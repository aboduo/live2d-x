#include "PlistParser.h"
#include "CCTypes.h"

class XmlSaxHander : public tinyxml2::XMLVisitor
{
public:
	XmlSaxHander()
        :m_ccsaxParserImp(0)
    {
        
    }
	
	virtual bool VisitEnter( const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute );
	virtual bool VisitExit( const tinyxml2::XMLElement& element );
	virtual bool Visit( const tinyxml2::XMLText& text );
	virtual bool Visit( const tinyxml2::XMLUnknown&){ return true; }

	void setCCSAXParserImp(CCSAXParser* parser)
	{
		m_ccsaxParserImp = parser;
	}

private:
	CCSAXParser *m_ccsaxParserImp;
};



bool XmlSaxHander::VisitEnter( const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute )
{
	//CCLog(" VisitEnter %s",element.Value());

	std::vector<const char*> attsVector;
	for( const tinyxml2::XMLAttribute* attrib = firstAttribute; attrib; attrib = attrib->Next() )
	{
		//CCLog("%s", attrib->Name());
		attsVector.push_back(attrib->Name());
		//CCLog("%s",attrib->Value());
		attsVector.push_back(attrib->Value());
	}
    
    // nullptr is used in c++11
	//attsVector.push_back(nullptr);
    attsVector.push_back(NULL);

	CCSAXParser::startElement(m_ccsaxParserImp, (const CC_XML_CHAR *)element.Value(), (const CC_XML_CHAR **)(&attsVector[0]));
	return true;
}
bool XmlSaxHander::VisitExit( const tinyxml2::XMLElement& element )
{
	//CCLog("VisitExit %s",element.Value());

	CCSAXParser::endElement(m_ccsaxParserImp, (const CC_XML_CHAR *)element.Value());
	return true;
}

bool XmlSaxHander::Visit( const tinyxml2::XMLText& text )
{
	//CCLog("Visit %s",text.Value());
	CCSAXParser::textHandler(m_ccsaxParserImp, (const CC_XML_CHAR *)text.Value(), (unsigned int)strlen(text.Value()));
	return true;
}

CCSAXParser::CCSAXParser()
{
    m_pDelegator = NULL;
}

CCSAXParser::~CCSAXParser(void)
{
}

bool CCSAXParser::init(const char *pszEncoding)
{
    CC_UNUSED_PARAM(pszEncoding);
    // nothing to do
    return true;
}

bool CCSAXParser::parse(const char* pXMLData, unsigned int uDataLength)
{
	tinyxml2::XMLDocument tinyDoc;
	tinyDoc.Parse(pXMLData, uDataLength);
	XmlSaxHander printer;
	printer.setCCSAXParserImp(this);
	
	return tinyDoc.Accept( &printer );	
}

bool CCSAXParser::parse(const char *pszFile)
{
    bool bRet = false;
    long pSize = 0;
//    unsigned char* pBuffer;
//    FILE *fp = fopen(pszFile, "rb");
    
//    fseek(fp,0,SEEK_END);
//    pSize = ftell(fp);
//    fseek(fp,0,SEEK_SET);
//    pBuffer = new unsigned char[pSize];
//    pSize = fread(pBuffer,sizeof(unsigned char), pSize,fp);
//    fclose(fp);
//    if(pBuffer)
//    {
//        bRet = parse((const char*)pBuffer, (unsigned int)pSize);
//    }
    QFile file(pszFile);
    if(file.open(QFile::ReadOnly|QFile::Text))
    {
        QByteArray pBuffer = file.readAll();
        pSize = pBuffer.size();
        if (pBuffer != "" && pSize > 0)
        {
            bRet = parse(pBuffer.data(), (unsigned int)pSize);
        }
        file.close();
    }
    return bRet;
}

void CCSAXParser::startElement(void *ctx, const CC_XML_CHAR *name, const CC_XML_CHAR **atts)
{
    ((CCSAXParser*)(ctx))->m_pDelegator->startElement(ctx, (char*)name, (const char**)atts);
}

void CCSAXParser::endElement(void *ctx, const CC_XML_CHAR *name)
{
    ((CCSAXParser*)(ctx))->m_pDelegator->endElement(ctx, (char*)name);
}
void CCSAXParser::textHandler(void *ctx, const CC_XML_CHAR *name, int len)
{
    ((CCSAXParser*)(ctx))->m_pDelegator->textHandler(ctx, (char*)name, len);
}
void CCSAXParser::setDelegator(CCSAXDelegator* pDelegator)
{
    m_pDelegator = pDelegator;
}


CCDictMaker::CCDictMaker()        
    : m_eResultType(SAX_RESULT_NONE),
      m_pRootArray(NULL), 
      m_pRootDict(NULL),
      m_pCurDict(NULL),
      m_tState(SAX_NONE),
      m_pArray(NULL)
{
}

CCDictMaker::~CCDictMaker()
{
}

CCDictionary* CCDictMaker::dictionaryWithContentsOfFile(const char *pFileName)
{
    m_eResultType = SAX_RESULT_DICT;
    CCSAXParser parser;

    if (false == parser.init("UTF-8"))
    {
        return NULL;
    }
    parser.setDelegator(this);

    parser.parse(pFileName);
    return m_pRootDict;
}

CCArray* CCDictMaker::arrayWithContentsOfFile(const char* pFileName)
{
    m_eResultType = SAX_RESULT_ARRAY;
    CCSAXParser parser;

    if (false == parser.init("UTF-8"))
    {
        return NULL;
    }
    parser.setDelegator(this);

    parser.parse(pFileName);
    return m_pArray;
}

void CCDictMaker::startElement(void *ctx, const char *name, const char **atts)
{
    CC_UNUSED_PARAM(ctx);
    CC_UNUSED_PARAM(atts);
    std::string sName((char*)name);
    if( sName == "dict" )
    {
        m_pCurDict = new CCDictionary();
        if(m_eResultType == SAX_RESULT_DICT && m_pRootDict == NULL)
        {
            // Because it will call m_pCurDict->release() later, so retain here.
            m_pRootDict = m_pCurDict;
            m_pRootDict->retain();
        }
        m_tState = SAX_DICT;

        CCSAXState preState = SAX_NONE;
        if (! m_tStateStack.empty())
        {
            preState = m_tStateStack.top();
        }

        if (SAX_ARRAY == preState)
        {
            // add the dictionary into the array
            m_pArray->addObject(m_pCurDict);
        }
        else if (SAX_DICT == preState)
        {
            // add the dictionary into the pre dictionary
            CCAssert(! m_tDictStack.empty(), "The state is wrong!");
            CCDictionary* pPreDict = m_tDictStack.top();
            pPreDict->setObject(m_pCurDict, m_sCurKey.c_str());
        }

        m_pCurDict->release();

        // record the dict state
        m_tStateStack.push(m_tState);
        m_tDictStack.push(m_pCurDict);
    }
    else if(sName == "key")
    {
        m_tState = SAX_KEY;
    }
    else if(sName == "integer")
    {
        m_tState = SAX_INT;
    }
    else if(sName == "real")
    {
        m_tState = SAX_REAL;
    }
    else if(sName == "string")
    {
        m_tState = SAX_STRING;
    }
    else if (sName == "array")
    {
        m_tState = SAX_ARRAY;
        m_pArray = new CCArray();
        if (m_eResultType == SAX_RESULT_ARRAY && m_pRootArray == NULL)
        {
            m_pRootArray = m_pArray;
            m_pRootArray->retain();
        }
        CCSAXState preState = SAX_NONE;
        if (! m_tStateStack.empty())
        {
            preState = m_tStateStack.top();
        }

        if (preState == SAX_DICT)
        {
            m_pCurDict->setObject(m_pArray, m_sCurKey.c_str());
        }
        else if (preState == SAX_ARRAY)
        {
            CCAssert(! m_tArrayStack.empty(), "The state is wrong!");
            CCArray* pPreArray = m_tArrayStack.top();
            pPreArray->addObject(m_pArray);
        }
        m_pArray->release();
        // record the array state
        m_tStateStack.push(m_tState);
        m_tArrayStack.push(m_pArray);
    }
    else
    {
        m_tState = SAX_NONE;
    }
}

void CCDictMaker::endElement(void *ctx, const char *name)
{
    CC_UNUSED_PARAM(ctx);
    CCSAXState curState = m_tStateStack.empty() ? SAX_DICT : m_tStateStack.top();
    std::string sName((char*)name);
    if( sName == "dict" )
    {
        m_tStateStack.pop();
        m_tDictStack.pop();
        if ( !m_tDictStack.empty())
        {
            m_pCurDict = m_tDictStack.top();
        }
    }
    else if (sName == "array")
    {
        m_tStateStack.pop();
        m_tArrayStack.pop();
        if (! m_tArrayStack.empty())
        {
            m_pArray = m_tArrayStack.top();
        }
    }
    else if (sName == "true")
    {
        CCString *str = new CCString("1");
        if (SAX_ARRAY == curState)
        {
            m_pArray->addObject(str);
        }
        else if (SAX_DICT == curState)
        {
            m_pCurDict->setObject(str, m_sCurKey.c_str());
        }
        str->release();
    }
    else if (sName == "false")
    {
        CCString *str = new CCString("0");
        if (SAX_ARRAY == curState)
        {
            m_pArray->addObject(str);
        }
        else if (SAX_DICT == curState)
        {
            m_pCurDict->setObject(str, m_sCurKey.c_str());
        }
        str->release();
    }
    else if (sName == "string" || sName == "integer" || sName == "real")
    {
        CCString* pStrValue = new CCString(m_sCurValue);

        if (SAX_ARRAY == curState)
        {
            m_pArray->addObject(pStrValue);
        }
        else if (SAX_DICT == curState)
        {
            m_pCurDict->setObject(pStrValue, m_sCurKey.c_str());
        }

        pStrValue->release();
        m_sCurValue.clear();
    }
    
    m_tState = SAX_NONE;
}

void CCDictMaker::textHandler(void *ctx, const char *ch, int len)
{
    CC_UNUSED_PARAM(ctx);
    if (m_tState == SAX_NONE)
    {
        return;
    }

    CCSAXState curState = m_tStateStack.empty() ? SAX_DICT : m_tStateStack.top();
    CCString *pText = new CCString(std::string((char*)ch,0,len));

    switch(m_tState)
    {
    case SAX_KEY:
        m_sCurKey = pText->getCString();
        break;
    case SAX_INT:
    case SAX_REAL:
    case SAX_STRING:
        {
            if (curState == SAX_DICT)
            {
                CCAssert(!m_sCurKey.empty(), "key not found : <integer/real>");
            }
            
            m_sCurValue.append(pText->getCString());
        }
        break;
    default:
        break;
    }
    pText->release();
}


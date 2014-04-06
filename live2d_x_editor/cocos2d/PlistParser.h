#ifndef PLISTPARSER_H
#define PLISTPARSER_H

#include <QString>
#include <QList>
#include <QStack>
#include <QMap>
#include "tinyxml2/tinyxml2.h"
#include "CCDictionary.h"
#include "CCArray.h"

typedef unsigned char CC_XML_CHAR;
#define CC_UNUSED_PARAM(unusedparam) (void)unusedparam

typedef enum 
{
    SAX_NONE = 0,
    SAX_KEY,
    SAX_DICT,
    SAX_INT,
    SAX_REAL,
    SAX_STRING,
    SAX_ARRAY
}CCSAXState;

typedef enum
{
    SAX_RESULT_NONE = 0,
    SAX_RESULT_DICT,
    SAX_RESULT_ARRAY
}CCSAXResult;


class CCSAXDelegator
{
public:
    virtual void startElement(void *ctx, const char *name, const char **atts) = 0;
    virtual void endElement(void *ctx, const char *name) = 0;
    virtual void textHandler(void *ctx, const char *s, int len) = 0;
};

class CCSAXParser
{
    CCSAXDelegator*    m_pDelegator;
public:

    CCSAXParser();
    ~CCSAXParser(void);

    bool init(const char *pszEncoding);
    bool parse(const char* pXMLData, unsigned int uDataLength);
    bool parse(const char *pszFile);
    void setDelegator(CCSAXDelegator* pDelegator);

    static void startElement(void *ctx, const CC_XML_CHAR *name, const CC_XML_CHAR **atts);
    static void endElement(void *ctx, const CC_XML_CHAR *name);
    static void textHandler(void *ctx, const CC_XML_CHAR *name, int len);
};


class CCDictMaker : public CCSAXDelegator
{
public:
    CCDictMaker() ;

    ~CCDictMaker();

    CCDictionary* dictionaryWithContentsOfFile(const char *pFileName);

    CCArray* arrayWithContentsOfFile(const char* pFileName);

    void startElement(void *ctx, const char *name, const char **atts);

    void endElement(void *ctx, const char *name);

    void textHandler(void *ctx, const char *ch, int len);
    
public:
    CCSAXResult m_eResultType;
    CCArray* m_pRootArray;
    CCDictionary *m_pRootDict;
    CCDictionary *m_pCurDict;
    QStack<CCDictionary*> m_tDictStack;
    std::string m_sCurKey;   ///< parsed key
    std::string m_sCurValue; // parsed value
    CCSAXState m_tState;
    CCArray* m_pArray;

    QStack<CCArray*> m_tArrayStack;
    QStack<CCSAXState>  m_tStateStack;
};


#endif // PLISTPARSER_H

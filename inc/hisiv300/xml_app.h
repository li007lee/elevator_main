
#ifndef __Mapport__xml_app__
#define __Mapport__xml_app__
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include "mem_app.h"

#define _MAX_BLOCK_SIZE				(1024*10)
#define XML_TRY     __try(&except)
#define XML_EXCEPT  __except
#define XML_ENDTRY  __endtry(&except)
#define XML_STR        (xmlChar *)

typedef char xmlChar;
struct _xmlDoc;
struct _xmlNode;
struct _xmlAttribute;

typedef struct _xmlDoc xmlDoc;
typedef struct _xmlNode xmlNode;
typedef struct _xmlAttribute xmlAttribute;
typedef int (*xmlGetChar)(void *ctx);
typedef int (*File2MemxmlGetChar)(char **ctx);
typedef int (*xmlUngetChar)(void *ctx, int ch);
typedef int (*File2MemxmlGetTagAndValue)(xmlDoc *doc,void *param,char *tags,char *values);

typedef int (*xmlWriteString)(const xmlChar *string, void *ctx);
typedef int (*xmlWriteMultiString)(void *ctx, ...);

typedef int (*xmlWriteStringToMem)(xmlDoc *doc, const xmlChar *string);
typedef int (*xmlWriteMultiStringToMem)(xmlDoc *doc, ...);
void xmlFreeDoc(xmlDoc *doc);

struct _xmlDoc
{
    xmlNode *root;
    xmlNode *last;
    xmlNode *current;
    mem_t mem;
    xmlChar *buffer;
    int bufferLen;
    int bufferIndex;
};

struct _xmlNode
{
    xmlDoc *doc;
    xmlNode *parent;
    xmlNode *next;
    xmlNode *first;
    xmlNode *last;
    xmlAttribute *firstAttr;
    xmlAttribute *lastAttr;
    xmlChar *name;
    xmlChar *text;
};

struct _xmlAttribute
{
    xmlNode *parent;
    xmlAttribute *next;
    xmlChar *name;
    xmlChar *text;
};

typedef struct _xmlInput
{
    xmlGetChar      getChar;
    void *ctx;
} xmlInput;

typedef struct _File2MemxmlInput
{
    File2MemxmlGetChar      getChar;
	File2MemxmlGetTagAndValue	getTagAndVal;
    char **ctx;
	void *param;
} File2MemxmlInput;



typedef struct _xmlOutput
{
    xmlWriteString  writeString;
    xmlWriteMultiString writeMultiString;
    void *ctx;
} xmlOutput;

typedef struct _xmlOutputToBuf
{
    xmlWriteStringToMem  writeString;
    xmlWriteMultiStringToMem writeMultiString;
} xmlOutputToBuf;
#endif

xmlDoc *xmlNewDoc(xmlChar *name);
xmlNode *xmlNewChild(xmlDoc *doc, xmlNode *parent, xmlChar *name, xmlChar *text);

int xmlOutputDoc(xmlDoc *doc, xmlOutput *output, int outputHeader);
int xmlOutputDocToMem(xmlDoc *doc, xmlOutputToBuf *output, int outputHeader);

int xmlOutputToFile(xmlDoc *doc, void *file, int outputHeader);

int xmlOutputToMem(xmlDoc *doc, int outputHeader);
xmlDoc *xmlParseFile(void *file);

xmlDoc *File2MemxmlParseToDoc(char *indata,void *param,File2MemxmlGetTagAndValue Fun);
xmlNode *xmlGetRootNode(xmlDoc *doc);
xmlNode *xmlGetFirstChild(xmlNode *parent);

xmlNode *xmlGetFirstChildByName(xmlNode *parent, xmlChar *name);

xmlNode *xmlGetNext(xmlNode *node);

xmlNode *xmlGetNextByName(xmlNode *node, xmlChar *name);

xmlChar *xmlGetName(xmlNode *node);

xmlChar *xmlGetText(xmlNode *node);
xmlAttribute *xmlAddAttribute(xmlDoc *doc, xmlNode *node, xmlChar *name, xmlChar *text);

xmlAttribute *xmlGetFirstAttribute(xmlNode *node);

xmlAttribute *xmlGetNextAttribute(xmlAttribute *attr);
xmlChar *xmlGetAttrName(xmlAttribute *attr);

xmlChar *xmlGetAttrText(xmlAttribute *attr);

xmlAttribute *xmlGetFirstAttributeByName(xmlNode *node, xmlChar *name);
xmlChar *xmlGetTextByAttributeName(xmlNode *node,xmlChar *name);//不允许同名属性

void xmlFreeDoc(xmlDoc *doc);

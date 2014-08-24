#ifndef UTILS_H
#define UTILS_H

#define XmlLoop(parentEntry, it) for(TiXmlElement *##it = parentEntry->FirstChildElement(); ##it != NULL; ##it = ##it->NextSiblingElement())


#endif

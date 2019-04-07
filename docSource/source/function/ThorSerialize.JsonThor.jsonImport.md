---
layout: function
generate: false
typeInfo:
    namespace: ThorsAnvil::Serialize
    header:    ThorSerialize/JsonThor.h
    function:  jsonImport
    description: 
    template:  template<typename T> 
    return:
        type: 'Importer<Json, T>'
        description: 
    parameters:
        - name: value
          type: 'T&'
          default: 
          description: 
        - name: parseStrictness
          type: 'ParserInterface::ParseType'
          default:  ParserInterface::ParseType::Weak
          description: 
        - name: catchExceptions
          type: 'bool'
          default:  false 
          description: 
children: []
---

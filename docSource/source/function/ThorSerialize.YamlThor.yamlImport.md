---
layout: function
generate: false
typeInfo:
    namespace: ThorsAnvil::Serialize
    header:    ThorSerialize/YamlThor.h
    function:  yamlImport
    description: 
    template:  template<typename T> 
    return:
        type: 'Importer<Yaml, T>'
        description: 'Object that can be passed to operator>> for de-serialization.'
    parameters:
        - name: value
          type: 'T&'
          default: 
          description: 'The object to be de-serialized.'
        - name: parseStrictness
          type: 'ParserInterface::ParseType'
          default:  ParserInterface::ParseType::Weak
          description: 'Weak: ignore missing extra fields. Strict: Any missing or extra fields throws exception.'
        - name: catchExceptions
          type: 'bool'
          default:  false 
          description: 
children: []
---

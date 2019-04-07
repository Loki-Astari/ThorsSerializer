---
layout: function
generate: false
typeInfo:
    namespace: ThorsAnvil::Serialize
    header:    ThorSerialize/BinaryThor.h
    function:  binImport
    description: 
    template:  template<typename T> 
    return:
        type: 'Importer<Binary<T>, T>'
        description: 'Object that can be passed to operator>> for de-serialization.'
    parameters:
        - name: value
          type: 'T&'
          default: 
          description: 'The object to be de-serialized.'
        - name: catchExceptions
          type: 'bool'
          default:  false 
          description: 
children: []
---

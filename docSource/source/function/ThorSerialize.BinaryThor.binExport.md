---
layout: function
generate: false
typeInfo:
    namespace: ThorsAnvil::Serialize
    header:    ThorSerialize/BinaryThor.h
    function:  binExport
    description: 
    template:  template<typename T> 
    return:
        type: 'Exporter<Binary<T>, T>'
        description: 'Object that can be passed to operator<< for serialization.'
    parameters:
        - name: value
          type: 'T const&'
          default: 
          description: 'The object to be serialized.'
        - name: catchExceptions
          type: 'bool'
          default:  false 
          description: 
children: []
---

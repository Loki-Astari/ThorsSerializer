---
layout: package
generate: false
nameSpace: 
headers:
    base: ThorSerialize/Traits.h
    files:
        - name:
          functions:
            - name:     ThorsAnvil_MakeEnum
              param:    [ EnumType, EnumValues... ]
              showParam: true
            - name:     ThorsAnvil_MakeTraitCustom
              param:    [ Type ]
              showParam: true
            - name:     ThorsAnvil_PointerAllocator
              param:    [ Type, Action]
              showParam: true
            - name:     ThorsAnvil_MakeTrait
              param:    [ Type, fields...]
              showParam: true
            - name:     ThorsAnvil_ExpandTrait
              param:    [ ParentType, Type, fields...]
              showParam: true
            - name:     ThorsAnvil_Template_MakeTrait
              param:    [ TemplateParameterCount, Type, fields... ]
              showParam: true
            - name:     ThorsAnvil_Template_ExpandTrait
              param:    [ TemplateParameterCount, ParentType, Type, fields... ]
              showParam: true
            - name:     ThorsAnvil_PolyMorphicSerializer
              param:    [ Type ]
              showParam: true
            - name:     ThorsAnvil_RegisterPolyMorphicType
              param:    [ Type ]
              showParam: true

    notes: This was copied from package/ThorSerialize.md and made to look nice
           thus it must be manially maintained.
---

---
layout: package
generate: false
nameSpace:  ThorsAnvil::Serialize
headers:
    base: ThorSerialize/Exporter.h
    files:
        - name:
          functions:
            - return: std::ostream&
              name:   operator<<
              param:  [   std::ostream& stream, Exporter const& data ]
              showParam: true
    notes: This was copied from package/ThorSerialize.md and made to look nice
           thus it must be manially maintained.
---

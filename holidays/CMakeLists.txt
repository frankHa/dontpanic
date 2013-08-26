set(LIBKHOLIDAYS_DATA_DIR ${KDEPIMLIBS_DATA_DIR}/libkholidays/plan2)

set(HOLIDAYS
    holiday_de-he_de
   )
   
install( FILES ${HOLIDAYS} DESTINATION ${LIBKHOLIDAYS_DATA_DIR})

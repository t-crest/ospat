#
#

add_executable(elf2uart elf2uart.cc)

target_link_libraries(elf2uart ${ELF} ${Boost_LIBRARIES})

install(TARGETS elf2uart RUNTIME DESTINATION bin)

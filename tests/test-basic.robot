# test-basic.robot

*** Settings ***
# Boilerplate
Suite Setup       Setup
Suite Teardown    Teardown
Test Setup        Reset Emulation
Resource          ${RENODEKEYWORDS}

*** Variables ***
# Our shell prompt to expect
# ${SHELL_PROMPT}    shell>

*** Keywords ***
Start Test
    # Create the Machine
    Execute Command             mach create
    Execute Command             machine LoadPlatformDescription @platforms/cpus/zynq-7000.repl

    # Load the ELF file
    Execute Command             sysbus LoadELF @${PWD_PATH}/Debug/FultronOS.elf

    # Connect the UART
    Create Terminal Tester      sysbus.uart0

    Start Emulation

*** Test Cases ***
Test
    [Documentation]             Kernel welcome message
    [Tags]                      non_critical

    Start Test

    Wait For Line On Uart       >                      timeout=2
    Write Line To Uart          ping
    Wait For Line On Uart       Received: ping         timeout=2
#    Wait For Line On Uart       UART1_BASE: 0xe0000000 timeout=2
#    Wait For Line On Uart       UART1_BASE: 0xe0001000 timeout=2
#    Wait For Line On Uart       Float test: 3.14159    timeout=2
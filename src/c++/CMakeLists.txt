# Copyright (C) 2023 Fondazione Istituto Italiano di Tecnologia (IIT)  
# All Rights Reserved.
# Authors: Francesco Brand <francesco.brand@iit.it>

add_executable(${PROJECT_NAME} src/main.cpp)
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
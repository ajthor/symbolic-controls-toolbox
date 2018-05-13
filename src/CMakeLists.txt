
set(SRC
  models/state_space.cc
)

set(HEADERS
  models/state_space.h
)

add_library(controls SHARED ${SRC})

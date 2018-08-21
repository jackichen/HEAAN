set(HEAAN_HEADER_FILES Ciphertext.h Common.h Context.h EvaluatorUtils.h HEAAN.h Key.h
        NumUtils.h Plaintext.h Ring2Utils.h Scheme.h SchemeAlgo.h SecretKey.h
        SerializationUtils.h StringUtils.h TestScheme.h TimeUtils.h)
set(HEAAN_SOURCE_FILES Ciphertext.cpp Context.cpp EvaluatorUtils.cpp Key.cpp
        NumUtils.cpp Plaintext.cpp Ring2Utils.cpp Scheme.cpp SchemeAlgo.cpp SecretKey.cpp
        SerializationUtils.cpp StringUtils.cpp TestScheme.cpp TimeUtils.cpp)

add_library(HEAAN STATIC ${HEAAN_HEADER_FILES} ${HEAAN_SOURCE_FILES})
target_link_libraries(HEAAN ntl gmp)

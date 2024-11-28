add_executable(xapp_kpm_rc_a1
        xapp_kpm_rc.c
        ../../../../src/util/alg_ds/alg/defer.c
        policy_api.c
)

target_link_libraries(xapp_kpm_rc_a1
        PUBLIC
        e42_xapp
        -pthread
        -lsctp
        -ldl
        -lcurl
        -lcjson
)


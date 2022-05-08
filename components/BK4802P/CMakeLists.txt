set(component_srcs
    "src/bk4802p.c"
    )

idf_component_register(SRCS "${component_srcs}"
        INCLUDE_DIRS "include" "../../main"
        PRIV_INCLUDE_DIRS ""
        PRIV_REQUIRES "driver"
        REQUIRES "m5atom"
	)

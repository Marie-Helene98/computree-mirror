linux {
    GSL_BASE_PATH = "/usr/"

    GSL_INC_PATH = "$${GSL_BASE_PATH}include/gsl"
    GSL_LIBS_PATH = "$${GSL_BASE_PATH}lib/x86_64-linux-gnu"
}

win32 {
    GSL_BASE_PATH = "$${VCPKG_PATH}/"

    GSL_INC_PATH = "$${GSL_BASE_PATH}include"
    
    CONFIG(debug, debug|release) {
        GSL_LIBS_PATH = "$${GSL_BASE_PATH}debug/lib"
	GSL_BIN_PATH = "$${GSL_BASE_PATH}debug/bin"
    } else {
	GSL_LIBS_PATH = "$${GSL_BASE_PATH}lib"
	GSL_BIN_PATH = "$${GSL_BASE_PATH}bin"
    }
}

macx {
    GSL_BASE_PATH = "/usr/local/Cellar/gsl/2.6/"

    GSL_INC_PATH = "$${GSL_BASE_PATH}include/gsl"
    GSL_LIBS_PATH = "$${GSL_BASE_PATH}lib"
}

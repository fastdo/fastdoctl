#pragma once

bool API_get_os_version( SharedPointer<HttpRequestCtx> requestCtxPtr, Response & RSP, StringArray & urlPathPartArr, size_t i );

bool API_check_compiler( SharedPointer<HttpRequestCtx> requestCtxPtr, Response & RSP, StringArray & urlPathPartArr, size_t i );

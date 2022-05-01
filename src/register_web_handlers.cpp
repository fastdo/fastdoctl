#include "functional.hpp"

void RegisterWebHandlers( eienwebx::HttpApp & app )
{
    app.crossRoute( "*", "/", [] ( winux::SharedPointer<HttpRequestCtx> requestCtxPtr, eienwebx::Response & RSP, winux::StringArray const & urlPathPartArr, size_t i ) -> bool {
        RSP.header["Access-Control-Allow-Origin"] = "*";
        return true;
    } );

    cout << GetOsVersion() << endl;
}

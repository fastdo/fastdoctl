
#include "ctl_common.hpp"
#include "ctl_ControlCenterApp.hpp"
#include "ctl_web_handlers.hpp"
#include "ctl_api_handlers.hpp"


void RegisterWebHandlers( ControlCenterApp & app )
{
    app.crossRoute( "*", "/", [] ( SharedPointer<HttpRequestCtx> requestCtxPtr, Response & RSP, StringArray const & urlPathPartArr, size_t i ) -> bool {
        RSP.header["Access-Control-Allow-Origin"] = "*";
        return true;
    } );

    app.crossRoute( "*", "/api", [] ( SharedPointer<HttpRequestCtx> requestCtxPtr, Response & RSP, StringArray const & urlPathPartArr, size_t i ) -> bool {

        ControlCenterApp * ccApp = static_cast<ControlCenterApp *>(requestCtxPtr->app);
        String apiName = StrJoinEx( "/", urlPathPartArr, i + 1 );
        cout << Mixed(apiName).myJson() << endl;

        cout << NormalizePath(ccApp->httpConfig.documentRoot) << endl;

        cout << ccApp->_httpExternalData.serverPath << endl;

        return false;
    } );
}

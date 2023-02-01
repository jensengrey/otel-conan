#include "opentelemetry/exporters/otlp/otlp_http_exporter_factory.h"
#include "opentelemetry/exporters/otlp/otlp_http_exporter_options.h"
#include "opentelemetry/exporters/ostream/span_exporter_factory.h"
#include "opentelemetry/sdk/trace/simple_processor_factory.h"
#include "opentelemetry/sdk/trace/tracer_provider_factory.h"
#include "opentelemetry/sdk/version/version.h"
#include "opentelemetry/trace/provider.h"

#include <iostream>
#include <chrono>

namespace trace_api      = opentelemetry::trace;
namespace trace_sdk      = opentelemetry::sdk::trace;
namespace trace_exporter = opentelemetry::exporter::trace;
namespace otlp           = opentelemetry::exporter::otlp;

namespace trace = opentelemetry::trace;
namespace nostd = opentelemetry::nostd;

namespace
{

opentelemetry::exporter::otlp::OtlpHttpExporterOptions opts;
// otlp::OtlpHttpExporterOptions opts;
// opts.url = "http://localhost:4318/v1/traces";

void InitTracer()
{

  auto exporter = otlp::OtlpHttpExporterFactory::Create(opts);
  // auto exporter  = trace_exporter::OStreamSpanExporterFactory::Create();
  auto processor = trace_sdk::SimpleSpanProcessorFactory::Create(std::move(exporter));
  std::shared_ptr<opentelemetry::trace::TracerProvider> provider =
      trace_sdk::TracerProviderFactory::Create(std::move(processor));

  // Set the global trace provider
  trace_api::Provider::SetTracerProvider(provider);
}

void CleanupTracer()
{
  std::shared_ptr<opentelemetry::trace::TracerProvider> none;
  trace_api::Provider::SetTracerProvider(none);
}

nostd::shared_ptr<trace::Tracer> get_tracer()
{
  auto provider = trace::Provider::GetTracerProvider();
  return provider->GetTracer("f1f2_funcs", OPENTELEMETRY_SDK_VERSION);
}

void f1()
{
  auto scoped_span = trace::Scope(get_tracer()->StartSpan("f1"));
}

void f2()
{
  auto scoped_span = trace::Scope(get_tracer()->StartSpan("f2"));

  f1();
  f1();
}

} 

void top_entry_point()
{
    auto scoped_span = trace::Scope(get_tracer()->StartSpan("library"));

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    f2();
}

int main(int argc, char** argv){
    opts.url = "http://192.168.233.129:4318/v1/traces";
    InitTracer();

    top_entry_point();
    std::cout << "v5 alsdfkjasldkfjsa" << std::endl;

    CleanupTracer();
    return 0;
}

# otel-conan

demo of using opentelemetry and conan.io build

* Work in configuring the http exporter https://opentelemetry.io/docs/instrumentation/cpp/exporters/
* see also https://github.com/open-telemetry/opentelemetry-cpp/tree/main/examples

```
git clone https://github.com/jensengrey/otel-conan
python3 -m venv conan.env
source conan.env/bin/activate
pip install conan
cd otel-conan
mkdir build && cd build
conan install .. --build=missing
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug
cmake --build .
./bin/md5
```

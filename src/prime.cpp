#include <napi.h>
#include <thread>
#include <chrono>

class MyAsyncWorker : public Napi::AsyncWorker
{
public:
    MyAsyncWorker(const Napi::Function &callback)
        : Napi::AsyncWorker(callback), primes(Napi::Array::New(Env())) {}

    void Execute() override
    {
        for (int i = 0; i < 5000; ++i)
        {
            if (isPrime(i))
            {
                primeNumbers.push_back(i);
            }
        }
    }

    void OnOK() override
    {
        Napi::HandleScope scope(Env());

        Napi::Array result = Napi::Array::New(Env());

        for (size_t i = 0; i < primeNumbers.size(); i++) {
            result.Set(i, Napi::Number::New(Env(), primeNumbers[i]));
        }

        Callback().Call({Env().Null(), result});
    }

private:
    bool isPrime(int n)
    {
        if (n <= 1)
            return false;
        if (n <= 3)
            return true;
        if (n % 2 == 0 || n % 3 == 0)
            return false;
        for (int i = 5; i * i <= n; i += 6)
        {
            if (n % i == 0 || n % (i + 2) == 0)
                return false;
        }
        return true;
    }

    Napi::Array primes;
    std::vector<int> primeNumbers;
};

Napi::Value StartAsyncTask(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() < 1 || !info[0].IsFunction())
    {
        Napi::TypeError::New(env, "Callback function expected").ThrowAsJavaScriptException();
        return env.Null();
    }

    Napi::Function cb = info[0].As<Napi::Function>();
    MyAsyncWorker *worker = new MyAsyncWorker(cb);
    worker->Queue();

    return env.Undefined();
}

Napi::Object InitAsync(Napi::Env env, Napi::Object exports)
{
    exports.Set(Napi::String::New(env, "startAsyncTask"), Napi::Function::New(env, StartAsyncTask));
    return exports;
}

NODE_API_MODULE(addon_async, InitAsync)
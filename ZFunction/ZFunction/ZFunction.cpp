template<typename returnType, typename... argType>
class ZLambdaInterface
{
public:
	returnType Call(argType... args)
	{
		return _Call(args...);
	}
	virtual returnType _Call(argType... args) = 0;
};

template<typename Lambda, typename returnType, typename... argType>
class ZLambda : public ZLambdaInterface<returnType, argType...>
{
public :
	ZLambda(const Lambda& lambda)
	{
		lambdaInstance = new Lambda(lambda);
	}

	~ZLambda()
	{
		if (lambdaInstance)
		{
			delete lambdaInstance;
		}
	}

	virtual returnType _Call(argType... args)
	{
		return (*lambdaInstance)(args...);
	}

	Lambda* lambdaInstance;
};

template<typename T>
class ZFunction;

template<typename returnType, typename... argType>
class ZFunction<returnType(argType...)>
{
public:
	ZFunction()
	{
		lambdaInterface = nullptr;
	}

	template<typename Lambda>
	ZFunction(const Lambda& lambda)
	{
		lambdaInterface = new ZLambda<Lambda, returnType, argType...>(lambda);
	}

	template<typename Lambda>
	ZFunction<returnType(argType...)>& operator = (const Lambda& lambda)
	{
		if (lambdaInterface)
		{
			delete lambdaInterface;
		}

		lambdaInterface = new ZLambda<Lambda, returnType, argType...>(lambda);
		return *this;
	}

	returnType operator()(argType... args)
	{
		return lambdaInterface->Call(args...);
	}

	ZLambdaInterface<returnType, argType...>*lambdaInterface;
};


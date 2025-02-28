#pragma once

#include "Forward.h"
#include "Type.h"

#include "Mathematics/Numeric.h"



namespace Engine::Template
{
	template<typename ...Parameters>
	struct Function;


	template<typename Return, typename ...Parameters>
	class Function<Return(Parameters ...)>
	{
	public:
		using ThisType = Function<Return(Parameters ...)>;


		Function()
			: callable(nullptr)
		{

		}
		template<typename Functor>
		Function(Functor functor)
			: callable( new Callable<Functor>(functor) )
		{
		
		}
		Function(ThisType&& other)
		{
			callable = other.callable;

			other.callable = nullptr;
		}
		Function(const ThisType& other)
			: callable( other.callable->Clone() )
		{

		}
		ThisType& operator=(ThisType&& other)
		{
			Swap( &callable, &other.callable );

			return *this;
		}
		ThisType& operator=(const ThisType& other)
		{
			this->~Function();
			callable = other.callable->Clone();

			return *this;
		}
		~Function()
		{
			delete callable;
		}


		Return operator()(Parameters... parameters)
		{
			return callable->Invoke( parameters... );
		}

		operator Bool()
		{
			return callable != nullptr;
		}
	private:
		struct ICallable
		{
			virtual Return Invoke(Parameters... parameters) = 0;
			virtual ICallable* Clone() const = 0;
		};


		template<typename Functor>
		struct Callable : ICallable
		{
			Functor functor;


			Callable(Functor functor)
				: functor(functor)
			{

			}


			virtual Return Invoke(Parameters... parameters) override
			{
				return functor( parameters... );
			}
			virtual ICallable* Clone() const override
			{
				return new Callable<Functor>(functor);
			}
		};
	private:
		ICallable* callable;
	};
}


namespace Engine
{
	/**
	* Encapsulates a method that has sizeof...(Parameters) parameters and returns a value of the type specified by the Return parameter
	* 
	* @remark
	* Wrapper for callable object(function object, lambda, function pointer)
	*/
	template<typename Return, typename ...Parameters>	using Function	= Template::Function<Return(Parameters ...)>;
	// Encapsulates a method that has sizeof...(Parameters) parameters and does not return a value
	template<typename ...Parameters>					using Action	= Function<Void, Parameters ...>;
}
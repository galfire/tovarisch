#include "test_helper.h"

#include <tov/memory/allocated_object.h>
#include <tov/memory/heap_area.h>

#include <tov/memory_config.h>

namespace
{
	class alignas(8) Foo
	{
	public:
		Foo(int i)
			: mInt(i)
		{
			std::cout << "ALLOCATING FOO (" << i << "): " << this << "\n";
		}

		~Foo()
		{
			std::cout << "DEALLOCATING FOO: " << this << "\n";
		}

	private:
		int mInt;
	};

	using Arena = tov::memory::ArenaFreelist<Foo>;

	class AllocatedFoo
		: public Foo
		, public tov::memory::AllocatedObject<Arena, 1_kb>
	{
	public:
		using Foo::Foo;
	};
}

TEST_CASE("AllocatedObject", "[None]")
{
	AllocatedFoo::reset();

	SECTION("allocate")
	{
		SECTION("oding sothingd")
		{
			std::cout << "STARTING ALLOCATED OBJECT TEST\n";
			{
				auto f = new AllocatedFoo(10);
				delete f;
			}
			{
				auto f = new AllocatedFoo(10);
				delete f;
			}
			{
				auto f = new AllocatedFoo(10);
				new AllocatedFoo(10);
				new AllocatedFoo(10);
				delete f;
			}
			std::cout << "ENDING ALLOCATED OBJECT TEST\n";
		}

		SECTION("MKAE UNQUE")
		{
			std::cout << "STARTING UNIQUE ALLOCATED OBJECT TEST\n";

			std::make_unique<AllocatedFoo>(45);
			std::make_unique<AllocatedFoo>(45);
			std::make_unique<AllocatedFoo>(45);

			std::cout << "ENDING UNIQUE ALLOCATED OBJECT TEST\n";
		}

		SECTION("adfadfadadsfadUNQUE")
		{
			std::cout << "STARTING crash ALLOCATED OBJECT TEST\n";

			CHECK_THROWS_AS(
				for (auto i = 0; true; i++)
				{
					new AllocatedFoo(i);
				},
				std::bad_alloc
			);

			std::cout << "ENDING CRASHHH ALLOCATED OBJECT TEST\n";
		}

		SECTION("yyhjkhjkhjhj")
		{
			auto f = new AllocatedFoo(10);
			CHECK((uintptr_t)f % alignof(Foo) == 0);
		}
	}
}

#include "test_helper.h"

#include <tov/memory/allocated_object.h>
#include <tov/memory/heap_area.h>

#include <tov/memory_config.h>

#include <vector>

namespace
{
	class alignas(8) Foo
	{
	public:
		Foo(int i)
			: mInt(i)
		{
			//std::cout << "ALLOCATING FOO (" << i << "): " << this << "\n";
		}

		~Foo()
		{
			//std::cout << "DEALLOCATING FOO: " << this << "\n";
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
		}

		SECTION("MKAE UNQUE")
		{
			std::make_unique<AllocatedFoo>(45);
			std::make_unique<AllocatedFoo>(45);
			std::make_unique<AllocatedFoo>(45);
		}

		SECTION("adfadfadadsfadUNQUE")
		{
			CHECK_THROWS_AS(
				for (auto i = 0; i < 1000; i++)
				{
					new AllocatedFoo(i);
				},
				std::bad_alloc
			);
		}

		SECTION("yyhjkhjkhjhj")
		{
			auto f = new AllocatedFoo(10);
			CHECK((uintptr_t)f % alignof(Foo) == 0);
		}
	}
}

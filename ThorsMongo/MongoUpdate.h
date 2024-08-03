#ifndef THORSANVIL_DB_MONGO_MONGO_UPDATE_H
#define THORSANVIL_DB_MONGO_MONGO_UPDATE_H

#include "ThorsMongoConfig.h"
#include "ThorsMongoCommon.h"
#include <iterator>

/*
 *
 * Usage expamples below assume the following:
 *  struct Person
 *  {
 *      std::string                 name;
 *      std::uint32_t               age;
 *      DateTime                    bDay;
 *      std::vector<std::string>    food;
 *  };
 *  template<typename T>
 *  struct AgeField
 *  {
 *      using CType = ConstructorType<T>;
 *      T       age;
 *  };
 *  template<typename T>
 *  struct BDayField
 *  {
 *      using CType = ConstructorType<T>;
 *      T       bDay;
 *  };
 *  template<typenam T>
 *  struct FoodField
 *  {
 *      using CType = ConstructorType<T>;
 *      T       food;
 *  };
 *  using FindByAge = AgeField<Eq>
 *
 * Update Operators:
 *      CurrentDate
 *      Inc
 *      Min
 *      Max
 *      Mul
 *      Set
 */

namespace ThorsAnvil::DB::Mongo
{
namespace QueryOp
{

/*
 * Current Date
 * Usage:
 *      using Update = CurrentDate<BDayField, SetDate>;
 *      mongo["db"]["collection"].findAndUpdateOne<People>(FindAgeEq{32}, Update{});    // Set bDat to today.
 */
struct SetDate
{
    using CType = bool;
    SetDate(bool){}
    std::string $type = "date";
};
struct SetTimeStamp
{
    using CType = bool;
    SetTimeStamp(bool){}
    std::string $type = "timestamp";
};
template<typename T>
concept IsDateTimeType = requires {T::$type;};

template<template<typename> typename T, typename Limit>
requires IsDateTimeType<Limit>
struct CurrentDate
{
    using CType = ConstructorType<T<Limit>>;
    CurrentDate() : $currentDate{CType{}}   {}
    T<Limit>    $currentDate;
};

/*
 *  using Update    = Inc<AgeField>;
 *  mongo["db"]["collection"].findAndUpdateOne<People>(FindAgeEq{32}, Update{2});   // Increase age by 2.
 */
template<template<typename> typename T>
struct Inc
{
    using CType = ConstructorType<T<std::uint32_t>>;
    Inc(CType init): $inc(init)     {}
    T<std::uint32_t>    $inc;
};
/*
 * Usage
 *  using Update = Min<AgeField>;
 *  mongo["db"]["collection"].findAndUpdateOne<People>(FindAgeEq{32}, Update{12});   // Set Age to the min of 12 or currentValue
 */
template<template<typename> typename T>
struct Min
{
    using CType = ConstructorType<T<std::uint32_t>>;
    Min(CType init): $min(init)     {}
    T<std::uint32_t>    $min;
};
/*
 * Usage
 *  using Update = Max<AgeField>;
 *  mongo["db"]["collection"].findAndUpdateOne<People>(FindAgeEq{32}, Update{12});   // Set Age to the max of 12 or currentValue
 */
template<template<typename> typename T>
struct Max
{
    using CType = ConstructorType<T<std::uint32_t>>;
    Max(CType init): $max(init)     {}
    T<std::uint32_t>    $max;
};
/*
 * Usage
 *  using Update = Mul<AgeField>;
 *  mongo["db"]["collection"].findAndUpdateOne<People>(FindAgeEq{32}, Update{2.6});   // Multiple the age by 2.6
 */
template<template<typename> typename T>
struct Mul
{
    using CType = ConstructorType<T<std::uint32_t>>;
    Mul(CType init): $mul(init)     {}
    T<std::uint32_t>    $mul;
};

/*
 * Usage
 *  using Update = Rename<AgeField>;
 *  mongo["db"]["collection"].findAndUpdateOne<People>(FindAgeEq{32}, Update{"originalAge"});   // rename the age field to "originalAge"
 */
template<template<typename> typename T>
struct Rename
{
    using CType = ConstructorType<T<std::string>>;
    Rename(CType init): $rename(init)     {}
    T<std::string>    $rename;
};

/*
 * Usage:
 *  using Update = Set<AgeField<std::uint32>>;
 *  mongo["db"]["collection"].findAndUpdateOne<People>(FindAgeEq{32}, Update{45});   // Set age to 45
 */
template<typename T>
struct Set
{
    using CType = ConstructorType<T>;
    Set(CType init): $set(std::move(init))     {}
    T           $set;
};

/*
 * Usage:
 *  using Update = SetOnInsert<AgeField<std::uint32>>;
 *  mongo["db"]["collection"].findAndUpdateOne<People>(FindAgeEq{32}, Update{45});   // Set age to 45
 */
template<typename T>
struct SetOnInsert
{
    using CType = ConstructorType<T>;
    SetOnInsert(CType init): $setOnInsert(std::move(init))     {}
    T           $setOnInsert;
};

/*
 * Usage:
 *  using Update = Unset<AgeField>;
 *  mongo["db"]["collection"].findAndUpdateOne<People>(FindAgeEq{32}, Update{});   // Removed the age field from the object
 */
template<template<typename> typename T>
struct Unset
{
    T<std::string>  $unset;
};

/*
 * Usage:
 *  using Update = AddToSet<FoodField<std::string>>;
 *  mongo["db"]["collection"].findAndUpdateOne<People>(FindAgeEq{32}, Update{"Ham"});   // Removed the age field from the object
 */
template<typename T>
struct AddToSet
{
    using CType = ConstructorType<T>;
    AddToSet(CType init): $addToSet(std::move(init)) {}
    T           $addToSet;
};

/*
 * Usage:
 *  using Update = PopFront<FoodField>;
 *  mongo["db"]["collection"].findAndUpdateOne<People>(FindAgeEq{32}, Update{});   // Removed the age field from the object
 */
template<template<typename> typename T>
struct PopFront
{
    using CType = ConstructorType<T<std::uint32_t>>;
    PopFront(): $pop(-1) {}
    T<std::uint32_t>    $pop;
};

/*
 * Usage:
 *  using Update = PopBack<FoodField>;
 *  mongo["db"]["collection"].findAndUpdateOne<People>(FindAgeEq{32}, Update{});   // Removed the age field from the object
 */
template<template<typename> typename T>
struct PopBack
{
    using CType = ConstructorType<T<std::uint32_t>>;
    PopBack(): $pop(1) {}
    T<std::uint32_t>    $pop;
};

/*
 * Usage:
 *  using Update = Pull<FoodField<std::string>>;
 *  mongo["db"]["collection"].findAndUpdateOne<People>(FindAgeEq{32}, Update{"Ham"});   // Removed the age field from the object
 *
 * or (You can use conditionals)
 *  using Update = Pull<FoodField<Lt<std::string>>>;
 *  mongo["db"]["collection"].findAndUpdateOne<People>(FindAgeEq{32}, Update{"Ham"});   // Removed the age field from the object
 */
template<typename T>
struct Pull
{
    using CType = ConstructorType<T>;
    Pull(CType init): $pull(std::move(init)) {}
    T           $pull;
};

/*
 * Usage:
 *  using Update = Push<FoodField<std::string>>;
 *  mongo["db"]["collection"].findAndUpdateOne<People>(FindAgeEq{32}, Update{"Ham"});   // Removed the age field from the object
 */
template<typename T>
struct Push
{
    using CType = ConstructorType<T>;
    Push(CType init): $push(std::move(init)) {}
    T           $push;
};

/*
 * Usage:
 *  using Update = PullAll<FoodField, std::string>;
 *  mongo["db"]["collection"].findAndUpdateOne<People>(FindAgeEq{32}, Update{{"Ham", "Jam", "Honey"}});   // Removed the age field from the object
 */
template<template<typename> typename T, typename V>
struct PullAll
{
    using CType = ConstructorType<T<std::vector<V>>>;
    PullAll(CType init): $pullAll(std::move(init)) {}
    T<std::vector<V>>           $pullAll;
};

/*
 * Usage:
 *  using Update = AddToSet<FoodField<Each<std::string>>>;
 *  mongo["db"]["collection"].findAndUpdateOne<People>(FindAgeEq{32}, Update{{"Ham", "Jam", "Honey"}});   // Removed the age field from the object
 */
template<typename T>
struct Each
{
    using CType = std::vector<T>;
    Each(CType init): $each(std::move(init)) {}
    std::vector<T>          $each;
};

/*
 * Usage:
 *  using Update = Push<FoodField<Position<std::string>>>;
 *  mongo["db"]["collection"].findAndUpdateOne<People>(FindAgeEq{32}, Update{{{"Ham", "Jam"}, 23}}});   // Removed the age field from the object
 */
template<typename T>
struct Position
{
    using CType = std::pair<std::vector<T>, std::int32_t>;
    Position(CType init): $each(std::move(init.first)), $position(init.second) {}
    std::vector<T>          $each;
    std::int32_t            $position;
};

/*
 * Usage:
    using Update = Push<FoodField<Slice<std::string>>>;
 *  mongo["db"]["collection"].findAndUpdateOne<People>(FindAgeEq{32}, Update{{{"Ham", "Jam"}, 23}}});   // Removed the age field from the object
 */
template<typename T>
struct Slice
{
    using CType = std::pair<std::vector<T>, std::int32_t>;
    Slice(CType init): $each(std::move(init.first)), $slice(init.second) {}
    std::vector<T>          $each;
    std::int32_t            $slice;
};

/*
 * Usage:
 *  using Update = Push<FoodField<Sort<std::string>>>;
 *  mongo["db"]["collection"].findAndUpdateOne<People>(FindAgeEq{32}, Update{{{"Ham", "Jam"}, SortOrder::Ascending}}});   // Removed the age field from the object
 */
template<typename T>
struct Sort
{
    using CType = std::pair<std::vector<T>, SortOrder>;
    Sort(CType init): $each(std::move(init.first)), $sort(static_cast<std::int32_t>(init.second)) {}
    std::vector<T>          $each;
    std::int32_t            $sort;
};

}
}

ThorsAnvil_MakeTrait(               ThorsAnvil::DB::Mongo::QueryOp::SetDate,            $type);
ThorsAnvil_MakeTrait(               ThorsAnvil::DB::Mongo::QueryOp::SetTimeStamp,       $type);
ThorsAnvil_TTemplate_MakeTrait(2,   ThorsAnvil::DB::Mongo::QueryOp::CurrentDate,        $currentDate);
ThorsAnvil_TTemplate_MakeTrait(1,   ThorsAnvil::DB::Mongo::QueryOp::Inc,                $inc);
ThorsAnvil_TTemplate_MakeTrait(1,   ThorsAnvil::DB::Mongo::QueryOp::Min,                $min);
ThorsAnvil_TTemplate_MakeTrait(1,   ThorsAnvil::DB::Mongo::QueryOp::Max,                $max);
ThorsAnvil_TTemplate_MakeTrait(1,   ThorsAnvil::DB::Mongo::QueryOp::Mul,                $mul);
ThorsAnvil_TTemplate_MakeTrait(1,   ThorsAnvil::DB::Mongo::QueryOp::Rename,             $rename);
ThorsAnvil_Template_MakeTrait(1,    ThorsAnvil::DB::Mongo::QueryOp::Set,                $set);
ThorsAnvil_Template_MakeTrait(1,    ThorsAnvil::DB::Mongo::QueryOp::SetOnInsert,        $setOnInsert);
ThorsAnvil_TTemplate_MakeTrait(1,   ThorsAnvil::DB::Mongo::QueryOp::Unset,              $unset);
ThorsAnvil_Template_MakeTrait(1,    ThorsAnvil::DB::Mongo::QueryOp::AddToSet,           $addToSet);
ThorsAnvil_TTemplate_MakeTrait(1,   ThorsAnvil::DB::Mongo::QueryOp::PopFront,           $pop);
ThorsAnvil_TTemplate_MakeTrait(1,   ThorsAnvil::DB::Mongo::QueryOp::PopBack,            $pop);
ThorsAnvil_Template_MakeTrait(1,    ThorsAnvil::DB::Mongo::QueryOp::Pull,               $pull);
ThorsAnvil_Template_MakeTrait(1,    ThorsAnvil::DB::Mongo::QueryOp::Push,               $push);
ThorsAnvil_TTemplate_MakeTrait(2,   ThorsAnvil::DB::Mongo::QueryOp::PullAll,            $pullAll);
ThorsAnvil_Template_MakeTrait(1,    ThorsAnvil::DB::Mongo::QueryOp::Each,               $each);
ThorsAnvil_Template_MakeTrait(1,    ThorsAnvil::DB::Mongo::QueryOp::Position,           $each, $position);
ThorsAnvil_Template_MakeTrait(1,    ThorsAnvil::DB::Mongo::QueryOp::Slice,              $each, $slice);
ThorsAnvil_Template_MakeTrait(1,    ThorsAnvil::DB::Mongo::QueryOp::Sort,               $each, $sort);

#endif

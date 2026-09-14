#pragma once

#include <lib/Assert.h>
#include <lib/Numeric.h>
#include <lib/Object.h>
#include <lib/String.h>
#include <lib/collections/Array.h>
#include <lib/collections/Collection.h>
#include <lib/collections/Dictionary.h>
#include <lib/collections/comparators.h>
#include <lib/collections/List.h>
#include <lib/collections/Set.h>
#include <lib/exceptions.h>

#define output

#define DENY_COPYING(className) \
    className(const className&) = delete; \
    className& operator=(const className&) = delete

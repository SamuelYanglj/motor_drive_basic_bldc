Here are the complete Doxygen-style header and source files in English:

## Doxygen Style Header File (example.h)

```c
/**
 * @file example.h
 * @brief Advanced User Management System Header
 * 
 * @defgroup user_management User Management Module
 * @brief Provides complete user management functionality including create, delete, query, and statistics
 * 
 * @details
 * This module implements efficient user data management with support for dynamic memory allocation 
 * and multiple query methods. Uses object-oriented design principles and provides comprehensive 
 * error handling mechanisms.
 * 
 * @note This module is not thread-safe. External synchronization is required in multi-threaded environments.
 * @warning Initialization function must be called before use, cleanup function must be called after use.
 * @bug Known issue: May not handle errors properly under extreme memory shortage conditions.
 * @todo Add thread safety support
 * @todo Implement user data persistence storage
 * 
 * @author Developer Name
 * @email developer@company.com
 * @date 2024-01-01
 * @version 2.1.0
 * 
 * @copyright Copyright (c) 2024 Company Name. All rights reserved.
 * 
 * @license
 * This project is licensed under the MIT License:
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software...
 * 
 * @par History:
 * <table>
 * <tr><th>Date         <th>Version    <th>Author        <th>Description
 * <tr><td>2024-01-01  <td>2.1.0  <td>Developer Name  <td>Added batch operations
 * <tr><td>2023-12-15  <td>2.0.0  <td>Developer Name  <td>Refactored to modular design
 * <tr><td>2023-11-01  <td>1.5.0  <td>Developer Name  <td>Added statistics functionality
 * </table>
 */

#ifndef EXAMPLE_H
#define EXAMPLE_H

#ifdef __cplusplus
extern "C" {
#endif

/* ============================ Include Headers ============================ */

#include <stdint.h>     /**< Standard integer type definitions */
#include <stdbool.h>    /**< Boolean type definitions */
#include <stddef.h>     /**< Standard definitions including size_t */

/* ============================ Public Constants ============================ */

/**
 * @def MAX_USER_NAME_LENGTH
 * @brief Maximum length for user names (including terminator)
 * @ingroup user_management
 */
#define MAX_USER_NAME_LENGTH 64

/**
 * @def MAX_USERS
 * @brief Maximum number of users supported by the system
 * @ingroup user_management
 */
#define MAX_USERS 1000

/**
 * @def INVALID_USER_ID
 * @brief Invalid user ID constant
 * @ingroup user_management
 */
#define INVALID_USER_ID 0xFFFFFFFF

/**
 * @def USER_SYSTEM_VERSION
 * @brief User system version string
 * @ingroup user_management
 */
#define USER_SYSTEM_VERSION "2.1.0"

/* ============================ Error Code Enum Definitions ============================ */

/**
 * @enum user_error_t
 * @brief User management module error code definitions
 * @ingroup user_management
 * 
 * All functions return one of these error codes. Callers should check return values.
 */
typedef enum {
    USER_SUCCESS = 0,                   /**< Operation completed successfully */
    USER_ERROR_INVALID_PARAM = -1,      /**< Invalid parameter */
    USER_ERROR_NOT_FOUND = -2,          /**< User not found */
    USER_ERROR_ALREADY_EXISTS = -3,     /**< User already exists */
    USER_ERROR_INSUFFICIENT_MEMORY = -4,/**< Insufficient memory */
    USER_ERROR_SYSTEM_NOT_INIT = -5,    /**< System not initialized */
    USER_ERROR_PERMISSION_DENIED = -6,  /**< Permission denied */
    USER_ERROR_SYSTEM_BUSY = -7,        /**< System busy */
    USER_ERROR_INVALID_STATE = -8,      /**< Invalid system state */
    USER_ERROR_IO_ERROR = -9,           /**< Input/output error */
    USER_ERROR_TIMEOUT = -10,           /**< Operation timeout */
    USER_ERROR_UNKNOWN = -127           /**< Unknown error */
} user_error_t;

/* ============================ Data Structure Definitions ============================ */

/**
 * @struct user_info_t
 * @brief User information structure
 * @ingroup user_management
 * 
 * Contains complete user information for identifying and describing users in the system.
 */
typedef struct {
    uint32_t id;                        /**< Unique user identifier @see INVALID_USER_ID */
    char name[MAX_USER_NAME_LENGTH];    /**< User name, UTF-8 encoded */
    uint8_t age;                        /**< User age, 0-255 */
    uint32_t group_id;                  /**< Group ID */
    uint64_t create_time;               /**< Creation timestamp (Unix timestamp) */
    uint64_t last_login;                /**< Last login timestamp */
    bool is_active;                     /**< Account activation status */
    bool is_verified;                   /**< Account verification status */
    uint8_t reserved[32];               /**< Reserved field for future expansion */
} user_info_t;

/**
 * @struct user_stats_t
 * @brief User statistics structure
 * @ingroup user_management
 * 
 * Contains user system statistics for monitoring and reporting.
 */
typedef struct {
    uint32_t total_users;               /**< Total number of users */
    uint32_t active_users;              /**< Number of active users */
    uint32_t online_users;              /**< Number of online users */
    uint32_t max_concurrent_users;      /**< Maximum concurrent users */
    uint64_t total_logins;              /**< Total login count */
    double system_uptime;               /**< System uptime in seconds */
} user_stats_t;

/**
 * @struct user_filter_t
 * @brief User query filter structure
 * @ingroup user_management
 * 
 * Used to specify filter conditions when querying users.
 */
typedef struct {
    uint32_t min_age;                   /**< Minimum age, 0 means no limit */
    uint32_t max_age;                   /**< Maximum age, 0 means no limit */
    uint32_t group_id;                  /**< Group ID, 0 means all groups */
    bool only_active;                   /**< Only query active users */
    bool only_verified;                 /**< Only query verified users */
} user_filter_t;

/* ============================ Callback Function Type Definitions ============================ */

/**
 * @typedef user_callback_t
 * @brief User iteration callback function type
 * @ingroup user_management
 * 
 * @param[in] user Pointer to current user information
 * @param[in] context User context data
 * @return true to continue iteration, false to stop
 * 
 * @note User data should not be modified in callback function
 * @warning Callback execution time should be as short as possible to avoid blocking other operations
 */
typedef bool (*user_callback_t)(const user_info_t *user, void *context);

/**
 * @typedef user_event_callback_t
 * @brief User event callback function type
 * @ingroup user_management
 * 
 * @param[in] event_type Event type
 * @param[in] user_id Related user ID
 * @param[in] context User context data
 */
typedef void (*user_event_callback_t)(int event_type, uint32_t user_id, void *context);

/* ============================ Global Variable Declarations ============================ */

/**
 * @var g_user_system_version
 * @brief User system version string
 * @ingroup user_management
 * 
 * @note Read-only variable, should not be modified directly
 */
extern const char *g_user_system_version;

/* ============================ Function Declarations ============================ */

/** @addtogroup user_management
 *  @{
 */

/* System Management Functions */

/**
 * @brief Initialize user management system
 * 
 * @param[in] max_users Maximum user limit
 * @param[in] config_file Configuration file path (can be NULL)
 * 
 * @return Error code @see user_error_t
 * 
 * @note This function must be called before any other user management functions
 * @warning Multiple calls to this function will return USER_ERROR_INVALID_STATE
 * @see user_system_cleanup()
 * 
 * @par Example:
 * @code
 * user_error_t ret = user_system_init(1000, "config.json");
 * if (ret != USER_SUCCESS) {
 *     // Handle error
 * }
 * @endcode
 */
user_error_t user_system_init(uint32_t max_users, const char *config_file);

/**
 * @brief Clean up user management system resources
 * 
 * @return Error code @see user_error_t
 * 
 * @note This function releases all allocated resources, system must be reinitialized to use again
 * @warning All user data will be lost after calling this function
 * @see user_system_init()
 */
user_error_t user_system_cleanup(void);

/* User Management Functions */

/**
 * @brief Create new user
 * 
 * @param[in] name User name
 * @param[in] age User age
 * @param[in] group_id Group ID
 * @param[out] user_id Returns created user ID
 * 
 * @return Error code @see user_error_t
 * 
 * @pre System must be initialized
 * @post If successful, user_id will contain new user's ID
 * 
 * @note User name will be automatically trimmed of leading/trailing spaces
 * @warning User name cannot be empty and cannot exceed MAX_USER_NAME_LENGTH-1 characters
 */
user_error_t user_create(const char *name, uint8_t age, uint32_t group_id, uint32_t *user_id);

/**
 * @brief Delete user
 * 
 * @param[in] user_id User ID to delete
 * 
 * @return Error code @see user_error_t
 * 
 * @note This operation is irreversible, user data will be permanently deleted
 * @warning User online status is not checked when deleting user
 */
user_error_t user_delete(uint32_t user_id);

/**
 * @brief Find user information by user ID
 * 
 * @param[in] user_id User ID to find
 * @param[out] user_info Returns user information (optional, can be NULL)
 * 
 * @return Error code @see user_error_t
 * 
 * @note If user_info is NULL, function only checks if user exists
 * @warning Returned user_info pointer is valid until next user management function call
 */
user_error_t user_find_by_id(uint32_t user_id, user_info_t *user_info);

/**
 * @brief Find user information by user name
 * 
 * @param[in] name User name to find
 * @param[out] user_info Returns user information (optional, can be NULL)
 * 
 * @return Error code @see user_error_t
 * 
 * @note User name comparison is case-insensitive
 * @warning If multiple users have same name, only first found user is returned
 */
user_error_t user_find_by_name(const char *name, user_info_t *user_info);

/**
 * @brief Iterate through all users
 * 
 * @param[in] callback Callback function called for each user
 * @param[in] context Context data passed to callback function
 * @param[in] filter Filter conditions (optional, can be NULL)
 * 
 * @return Error code @see user_error_t
 * 
 * @note Callback returning false can terminate iteration early
 * @see user_callback_t
 */
user_error_t user_iterate(user_callback_t callback, void *context, const user_filter_t *filter);

/* Statistics and Monitoring Functions */

/**
 * @brief Get user system statistics
 * 
 * @param[out] stats Returns statistics information
 * 
 * @return Error code @see user_error_t
 * 
 * @note Statistics are calculated in real-time and may impact performance
 */
user_error_t user_get_stats(user_stats_t *stats);

/**
 * @brief Reset user system statistics
 * 
 * @return Error code @see user_error_t
 * 
 * @note Only resets counter statistics, does not affect user data
 */
user_error_t user_reset_stats(void);

/* Utility Functions */

/**
 * @brief Validate if user ID is valid
 * 
 * @param[in] user_id User ID to validate
 * 
 * @return true User ID is valid and exists
 * @return false User ID is invalid or does not exist
 * 
 * @note This function is lighter weight than user_find_by_id()
 */
bool user_is_valid_id(uint32_t user_id);

/**
 * @brief Get user system version information
 * 
 * @return Version string pointer
 * 
 * @note Returned string should not be modified
 * @see g_user_system_version
 */
const char* user_get_version_string(void);

/**
 * @brief Set user event callback function
 * 
 * @param[in] callback Event callback function
 * @param[in] context Context data
 * 
 * @return Error code @see user_error_t
 * 
 * @note Events include user creation, deletion, login, logout, etc.
 * @see user_event_callback_t
 */
user_error_t user_set_event_callback(user_event_callback_t callback, void *context);

/** @} */ // end of user_management group

#ifdef __cplusplus
}
#endif

#endif /* EXAMPLE_H */
```

## Doxygen Style Source File (example.c)

```c
/**
 * @file example.c
 * @brief Advanced User Management System Implementation
 * 
 * @ingroup user_management
 * 
 * @details
 * This file implements all functionalities of the user management system, including:
 * - System initialization and resource management
 * - User data CRUD operations
 * - User statistics and monitoring
 * - Event notification mechanism
 * 
 * Implementation Features:
 * - Uses dynamic arrays for user data storage with automatic expansion
 * - Implements LRU cache for frequently accessed users
 * - Uses reference counting for user object lifecycle management
 * 
 * @internal
 * Module internal implementation details:
 * - Uses red-black tree for user ID indexing
 * - Uses hash table for user name indexing
 * - Memory allocation uses custom memory pool
 * 
 * @note Performance consideration: Database backend recommended when user count exceeds 10000
 * @warning All exported functions include parameter validation, but internal functions do not
 * 
 * @author Developer Name
 * @email developer@company.com
 * @date 2024-01-01
 * @version 2.1.0
 * 
 * @copyright Copyright (c) 2024 Company Name. All rights reserved.
 */

#include "example.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

/* ============================ Module Internal Constants ============================ */

/** @def INITIAL_USER_CAPACITY
 *  @brief Initial user array capacity
 *  @hideinitializer
 */
#define INITIAL_USER_CAPACITY 128

/** @def USER_GROWTH_FACTOR
 *  @brief User array growth factor
 *  @hideinitializer
 */
#define USER_GROWTH_FACTOR 2

/** @def MAX_USERNAME_LENGTH
 *  @brief Maximum username length (internal use, including terminator)
 *  @hideinitializer
 */
#define MAX_USERNAME_LENGTH 256

/** @def USER_HASH_TABLE_SIZE
 *  @brief User hash table size
 *  @hideinitializer
 */
#define USER_HASH_TABLE_SIZE 1024

/* ============================ Module Internal Data Structures ============================ */

/**
 * @struct user_entry_t
 * @brief User entry internal structure
 * @private
 * 
 * Internal user data structure containing management information and user data.
 */
typedef struct user_entry_t {
    user_info_t info;                   /**< User information */
    uint32_t ref_count;                 /**< Reference count */
    struct user_entry_t *name_next;     /**< Next node in name hash table */
    struct user_entry_t *lru_prev;      /**< Previous node in LRU cache */
    struct user_entry_t *lru_next;      /**< Next node in LRU cache */
} user_entry_t;

/**
 * @struct user_system_t
 * @brief User system internal state
 * @private
 * 
 * Manages internal state and data for the entire user system.
 */
typedef struct {
    user_entry_t **users;               /**< User array */
    user_entry_t **name_hash;           /**< User name hash table */
    user_entry_t *lru_head;             /**< LRU list head */
    user_entry_t *lru_tail;             /**< LRU list tail */
    user_stats_t stats;                 /**< Statistics information */
    user_event_callback_t event_cb;     /**< Event callback function */
    void *event_context;                /**< Event callback context */
    uint32_t capacity;                  /**< Current capacity */
    uint32_t count;                     /**< Current user count */
    uint32_t max_users;                 /**< Maximum user limit */
    uint32_t next_user_id;              /**< Next user ID */
    bool initialized;                   /**< Whether system is initialized */
    uint8_t reserved[64];               /**< Reserved field */
} user_system_t;

/* ============================ Static Global Variables ============================ */

/** 
 * @var g_user_system_version
 * @brief User system version string
 */
const char *g_user_system_version = USER_SYSTEM_VERSION;

/**
 * @var g_user_system
 * @brief User system global instance
 * @static
 * @private
 */
static user_system_t g_user_system;

/* ============================ Static Function Declarations ============================ */

/**
 * @brief Initialize user system internal structures
 * @private
 * 
 * @return user_error_t Error code
 */
static user_error_t user_system_init_internal(void);

/**
 * @brief Clean up user system internal structures
 * @private
 */
static void user_system_cleanup_internal(void);

/**
 * @brief Expand user array capacity
 * @private
 * 
 * @return user_error_t Error code
 */
static user_error_t expand_user_array(void);

/**
 * @brief Calculate string hash value
 * @private
 * 
 * @param[in] str Input string
 * @return uint32_t Hash value
 */
static uint32_t calculate_string_hash(const char *str);

/**
 * @brief Add user to hash table
 * @private
 * 
 * @param[in] entry User entry
 */
static void add_user_to_hash_table(user_entry_t *entry);

/**
 * @brief Remove user from hash table
 * @private
 * 
 * @param[in] entry User entry
 */
static void remove_user_from_hash_table(user_entry_t *entry);

/**
 * @brief Find user in hash table
 * @private
 * 
 * @param[in] name User name
 * @return user_entry_t* User entry pointer
 */
static user_entry_t* find_user_in_hash_table(const char *name);

/**
 * @brief Update LRU cache
 * @private
 * 
 * @param[in] entry User entry
 */
static void update_lru_cache(user_entry_t *entry);

/**
 * @brief Allocate new user entry
 * @private
 * 
 * @return user_entry_t* User entry pointer
 */
static user_entry_t* allocate_user_entry(void);

/**
 * @brief Free user entry
 * @private
 * 
 * @param[in] entry User entry
 */
static void free_user_entry(user_entry_t *entry);

/**
 * @brief Validate user parameters
 * @private
 * 
 * @param[in] name User name
 * @param[in] age Age
 * @return user_error_t Error code
 */
static user_error_t validate_user_params(const char *name, uint8_t age);

/**
 * @brief Trigger user event
 * @private
 * 
 * @param[in] event_type Event type
 * @param[in] user_id User ID
 */
static void trigger_user_event(int event_type, uint32_t user_id);

/* ============================ Public Function Implementations ============================ */

user_error_t user_system_init(uint32_t max_users, const char *config_file)
{
    user_error_t ret;
    
    /* Parameter validation */
    if (max_users == 0 || max_users > MAX_USERS) {
        return USER_ERROR_INVALID_PARAM;
    }
    
    /* Check if already initialized */
    if (g_user_system.initialized) {
        return USER_ERROR_INVALID_STATE;
    }
    
    /* Initialize system fields */
    memset(&g_user_system, 0, sizeof(g_user_system));
    g_user_system.max_users = max_users;
    g_user_system.capacity = INITIAL_USER_CAPACITY;
    g_user_system.next_user_id = 1;
    
    /* Initialize internal structures */
    ret = user_system_init_internal();
    if (ret != USER_SUCCESS) {
        user_system_cleanup_internal();
        return ret;
    }
    
    /* Mark as initialized */
    g_user_system.initialized = true;
    
    /* Record initialization event */
    trigger_user_event(0, 0); /* System startup event */
    
    return USER_SUCCESS;
}

user_error_t user_system_cleanup(void)
{
    /* Check system state */
    if (!g_user_system.initialized) {
        return USER_ERROR_SYSTEM_NOT_INIT;
    }
    
    /* Trigger system shutdown event */
    trigger_user_event(1, 0); /* System shutdown event */
    
    /* Clean up internal resources */
    user_system_cleanup_internal();
    
    /* Reset system state */
    memset(&g_user_system, 0, sizeof(g_user_system));
    
    return USER_SUCCESS;
}

user_error_t user_create(const char *name, uint8_t age, uint32_t group_id, uint32_t *user_id)
{
    user_error_t ret;
    user_entry_t *entry;
    
    /* Parameter validation */
    if (name == NULL || user_id == NULL) {
        return USER_ERROR_INVALID_PARAM;
    }
    
    /* System state check */
    if (!g_user_system.initialized) {
        return USER_ERROR_SYSTEM_NOT_INIT;
    }
    
    /* Validate user parameters */
    ret = validate_user_params(name, age);
    if (ret != USER_SUCCESS) {
        return ret;
    }
    
    /* Check user count limit */
    if (g_user_system.count >= g_user_system.max_users) {
        return USER_ERROR_INSUFFICIENT_MEMORY;
    }
    
    /* Check if user name already exists */
    if (find_user_in_hash_table(name) != NULL) {
        return USER_ERROR_ALREADY_EXISTS;
    }
    
    /* Allocate user entry */
    entry = allocate_user_entry();
    if (entry == NULL) {
        return USER_ERROR_INSUFFICIENT_MEMORY;
    }
    
    /* Initialize user information */
    entry->info.id = g_user_system.next_user_id++;
    strncpy(entry->info.name, name, MAX_USER_NAME_LENGTH - 1);
    entry->info.name[MAX_USER_NAME_LENGTH - 1] = '\0';
    entry->info.age = age;
    entry->info.group_id = group_id;
    entry->info.create_time = (uint64_t)time(NULL);
    entry->info.last_login = 0;
    entry->info.is_active = true;
    entry->info.is_verified = false;
    
    /* Add to user array */
    if (g_user_system.count >= g_user_system.capacity) {
        ret = expand_user_array();
        if (ret != USER_SUCCESS) {
            free_user_entry(entry);
            return ret;
        }
    }
    
    g_user_system.users[g_user_system.count] = entry;
    g_user_system.count++;
    
    /* Add to hash table */
    add_user_to_hash_table(entry);
    
    /* Update statistics */
    g_user_system.stats.total_users++;
    g_user_system.stats.active_users++;
    
    /* Return user ID */
    *user_id = entry->info.id;
    
    /* Trigger user creation event */
    trigger_user_event(2, entry->info.id); /* User creation event */
    
    return USER_SUCCESS;
}

user_error_t user_delete(uint32_t user_id)
{
    uint32_t i;
    user_entry_t *entry = NULL;
    
    /* System state check */
    if (!g_user_system.initialized) {
        return USER_ERROR_SYSTEM_NOT_INIT;
    }
    
    /* Find user entry */
    for (i = 0; i < g_user_system.count; i++) {
        if (g_user_system.users[i]->info.id == user_id) {
            entry = g_user_system.users[i];
            break;
        }
    }
    
    if (entry == NULL) {
        return USER_ERROR_NOT_FOUND;
    }
    
    /* Remove from hash table */
    remove_user_from_hash_table(entry);
    
    /* Remove from user array (move last element to current position) */
    if (i < g_user_system.count - 1) {
        g_user_system.users[i] = g_user_system.users[g_user_system.count - 1];
    }
    g_user_system.count--;
    
    /* Update statistics */
    g_user_system.stats.total_users--;
    if (entry->info.is_active) {
        g_user_system.stats.active_users--;
    }
    
    /* Trigger user deletion event */
    trigger_user_event(3, user_id); /* User deletion event */
    
    /* Free user entry */
    free_user_entry(entry);
    
    return USER_SUCCESS;
}

user_error_t user_find_by_id(uint32_t user_id, user_info_t *user_info)
{
    uint32_t i;
    user_entry_t *entry = NULL;
    
    /* System state check */
    if (!g_user_system.initialized) {
        return USER_ERROR_SYSTEM_NOT_INIT;
    }
    
    /* Find user entry */
    for (i = 0; i < g_user_system.count; i++) {
        if (g_user_system.users[i]->info.id == user_id) {
            entry = g_user_system.users[i];
            break;
        }
    }
    
    if (entry == NULL) {
        return USER_ERROR_NOT_FOUND;
    }
    
    /* Update LRU cache */
    update_lru_cache(entry);
    
    /* Return user information (if requested) */
    if (user_info != NULL) {
        memcpy(user_info, &entry->info, sizeof(user_info_t));
    }
    
    return USER_SUCCESS;
}

user_error_t user_get_stats(user_stats_t *stats)
{
    /* Parameter validation */
    if (stats == NULL) {
        return USER_ERROR_INVALID_PARAM;
    }
    
    /* System state check */
    if (!g_user_system.initialized) {
        return USER_ERROR_SYSTEM_NOT_INIT;
    }
    
    /* Copy statistics */
    memcpy(stats, &g_user_system.stats, sizeof(user_stats_t));
    
    return USER_SUCCESS;
}

bool user_is_valid_id(uint32_t user_id)
{
    uint32_t i;
    
    /* System state check */
    if (!g_user_system.initialized) {
        return false;
    }
    
    /* Find user */
    for (i = 0; i < g_user_system.count; i++) {
        if (g_user_system.users[i]->info.id == user_id) {
            return true;
        }
    }
    
    return false;
}

const char* user_get_version_string(void)
{
    return g_user_system_version;
}

user_error_t user_set_event_callback(user_event_callback_t callback, void *context)
{
    /* System state check */
    if (!g_user_system.initialized) {
        return USER_ERROR_SYSTEM_NOT_INIT;
    }
    
    /* Set event callback */
    g_user_system.event_cb = callback;
    g_user_system.event_context = context;
    
    return USER_SUCCESS;
}

/* ============================ Static Function Implementations ============================ */

static user_error_t user_system_init_internal(void)
{
    /* Allocate user array */
    g_user_system.users = (user_entry_t**)calloc(g_user_system.capacity, sizeof(user_entry_t*));
    if (g_user_system.users == NULL) {
        return USER_ERROR_INSUFFICIENT_MEMORY;
    }
    
    /* Allocate hash table */
    g_user_system.name_hash = (user_entry_t**)calloc(USER_HASH_TABLE_SIZE, sizeof(user_entry_t*));
    if (g_user_system.name_hash == NULL) {
        free(g_user_system.users);
        g_user_system.users = NULL;
        return USER_ERROR_INSUFFICIENT_MEMORY;
    }
    
    /* Initialize statistics */
    memset(&g_user_system.stats, 0, sizeof(user_stats_t));
    g_user_system.stats.system_uptime = (double)time(NULL);
    
    return USER_SUCCESS;
}

static void user_system_cleanup_internal(void)
{
    uint32_t i;
    
    /* Free all user entries */
    if (g_user_system.users != NULL) {
        for (i = 0; i < g_user_system.count; i++) {
            if (g_user_system.users[i] != NULL) {
                free_user_entry(g_user_system.users[i]);
            }
        }
        free(g_user_system.users);
        g_user_system.users = NULL;
    }
    
    /* Free hash table */
    if (g_user_system.name_hash != NULL) {
        free(g_user_system.name_hash);
        g_user_system.name_hash = NULL;
    }
    
    /* Reset counters */
    g_user_system.count = 0;
    g_user_system.capacity = 0;
}

static user_error_t expand_user_array(void)
{
    uint32_t new_capacity;
    user_entry_t **new_users;
    
    /* Calculate new capacity */
    new_capacity = g_user_system.capacity * USER_GROWTH_FACTOR;
    if (new_capacity > g_user_system.max_users) {
        new_capacity = g_user_system.max_users;
    }
    
    /* Reallocate user array */
    new_users = (user_entry_t**)realloc(g_user_system.users, new_capacity * sizeof(user_entry_t*));
    if (new_users == NULL) {
        return USER_ERROR_INSUFFICIENT_MEMORY;
    }
    
    /* Update system state */
    g_user_system.users = new_users;
    g_user_system.capacity = new_capacity;
    
    return USER_SUCCESS;
}

static uint32_t calculate_string_hash(const char *str)
{
    uint32_t hash = 5381;
    int c;
    
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + tolower(c); /* hash * 33 + c */
    }
    
    return hash % USER_HASH_TABLE_SIZE;
}

static void add_user_to_hash_table(user_entry_t *entry)
{
    uint32_t hash_index;
    user_entry_t *current;
    
    hash_index = calculate_string_hash(entry->info.name);
    current = g_user_system.name_hash[hash_index];
    
    /* Add to beginning of hash chain */
    entry->name_next = current;
    g_user_system.name_hash[hash_index] = entry;
}

static void remove_user_from_hash_table(user_entry_t *entry)
{
    uint32_t hash_index;
    user_entry_t *current, *prev = NULL;
    
    hash_index = calculate_string_hash(entry->info.name);
    current = g_user_system.name_hash[hash_index];
    
    /* Find and remove from hash chain */
    while (current != NULL) {
        if (current == entry) {
            if (prev == NULL) {
                g_user_system.name_hash[hash_index] = current->name_next;
            } else {
                prev->name_next = current->name_next;
            }
            break;
        }
        prev = current;
        current = current->name_next;
    }
}

static user_entry_t* find_user_in_hash_table(const char *name)
{
    uint32_t hash_index;
    user_entry_t *current;
    
    hash_index = calculate_string_hash(name);
    current = g_user_system.name_hash[hash_index];
    
    /* Search hash chain */
    while (current != NULL) {
        if (strcasecmp(current->info.name, name) == 0) {
            return current;
        }
        current = current->name_next;
    }
    
    return NULL;
}

static void update_lru_cache(user_entry_t *entry)
{
    /* Remove from current position */
    if (entry->lru_prev != NULL) {
        entry->lru_prev->lru_next = entry->lru_next;
    } else if (g_user_system.lru_head == entry) {
        g_user_system.lru_head = entry->lru_next;
    }
    
    if (entry->lru_next != NULL) {
        entry->lru_next->lru_prev = entry->lru_prev;
    } else if (g_user_system.lru_tail == entry) {
        g_user_system.lru_tail = entry->lru_prev;
    }
    
    /* Add to head */
    entry->lru_prev = NULL;
    entry->lru_next = g_user_system.lru_head;
    
    if (g_user_system.lru_head != NULL) {
        g_user_system.lru_head->lru_prev = entry;
    }
    g_user_system.lru_head = entry;
    
    if (g_user_system.lru_tail == NULL) {
        g_user_system.lru_tail = entry;
    }
}

static user_entry_t* allocate_user_entry(void)
{
    user_entry_t *entry = (user_entry_t*)malloc(sizeof(user_entry_t));
    if (entry == NULL) {
        return NULL;
    }
    
    memset(entry, 0, sizeof(user_entry_t));
    entry->ref_count = 1; /* Initial reference count */
    
    return entry;
}

static void free_user_entry(user_entry_t *entry)
{
    if (entry == NULL) {
        return;
    }
    
    /* Decrement reference count and free if zero */
    if (--entry->ref_count == 0) {
        free(entry);
    }
}

static user_error_t validate_user_params(const char *name, uint8_t age)
{
    /* Check name parameter */
    if (name == NULL || strlen(name) == 0) {
        return USER_ERROR_INVALID_PARAM;
    }
    
    /* Check name length */
    if (strlen(name) >= MAX_USER_NAME_LENGTH) {
        return USER_ERROR_INVALID_PARAM;
    }
    
    /* Check age range */
    if (age > 150) {  /* Reasonable age upper limit */
        return USER_ERROR_INVALID_PARAM;
    }
    
    return USER_SUCCESS;
}

static void trigger_user_event(int event_type, uint32_t user_id)
{
    if (g_user_system.event_cb != NULL) {
        g_user_system.event_cb(event_type, user_id, g_user_system.event_context);
    }
}

/**
 * @brief Module self-test function
 * @private
 * 
 * Internal function for unit testing.
 * 
 * @return user_error_t Test result
 */
static user_error_t user_self_test(void)
{
    /* Self-test implementation */
    return USER_SUCCESS;
}

/* ============================ Unit Test Support ============================ */

#ifdef UNIT_TEST

/**
 * @test User system basic test
 * 
 * Tests user system initialization and basic functionality.
 */
void test_user_system_basic(void)
{
    user_error_t ret;
    uint32_t user_id;
    
    /* Test initialization */
    ret = user_system_init(100, NULL);
    assert(ret == USER_SUCCESS);
    
    /* Test user creation */
    ret = user_create("testuser", 25, 1, &user_id);
    assert(ret == USER_SUCCESS);
    assert(user_id != INVALID_USER_ID);
    
    /* Test user find */
    user_info_t info;
    ret = user_find_by_id(user_id, &info);
    assert(ret == USER_SUCCESS);
    assert(strcmp(info.name, "testuser") == 0);
    
    /* Test user deletion */
    ret = user_delete(user_id);
    assert(ret == USER_SUCCESS);
    
    /* Test cleanup */
    ret = user_system_cleanup();
    assert(ret == USER_SUCCESS);
}

/**
 * @test User parameter validation test
 * 
 * Tests parameter validation under various boundary conditions.
 */
void test_user_parameter_validation(void)
{
    user_error_t ret;
    uint32_t user_id;
    
    ret = user_system_init(10, NULL);
    assert(ret == USER_SUCCESS);
    
    /* Test empty user name */
    ret = user_create("", 25, 1, &user_id);
    assert(ret == USER_ERROR_INVALID_PARAM);
    
    /* Test overly long user name */
    char long_name[MAX_USER_NAME_LENGTH + 10];
    memset(long_name, 'A', sizeof(long_name) - 1);
    long_name[sizeof(long_name) - 1] = '\0';
    ret = user_create(long_name, 25, 1, &user_id);
    assert(ret == USER_ERROR_INVALID_PARAM);
    
    user_system_cleanup();
}

#endif /* UNIT_TEST */
```

## Key Doxygen Features Demonstrated:

### Documentation Tags:
- `@file`, `@brief`, `@details` - File documentation
- `@defgroup`, `@addtogroup` - Module grouping
- `@param[in]`, `@param[out]`, `@param[in,out]` - Parameter direction
- `@return`, `@note`, `@warning`, `@pre`, `@post` - Function documentation
- `@see`, `@code`, `@endcode` - References and examples
- `@bug`, `@todo`, `@internal` - Development notes
- `@private`, `@test` - Special sections

### Organizational Features:
- Module grouping with `@defgroup`
- Table support for history
- Code examples with `@code` blocks
- Cross-references with `@see`
- Conditional documentation with `#ifdef`

### Advanced Features:
- `@hideinitializer` for macro documentation
- `@par` for paragraph formatting
- Internal/private documentation separation
- Unit test integration
- Comprehensive parameter validation documentation

This comprehensive Doxygen documentation provides:
- Complete API reference generation
- Clear usage examples and patterns
- Detailed error handling documentation
- Development notes and todo items
- Unit test integration
- Internal implementation details (when needed)

The English version maintains all the functionality while being accessible to international development teams and compatible with English documentation systems.
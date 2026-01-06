以下是一个完整的Doxygen风格的.h文件和.c文件注释示例，包含了尽可能多的Doxygen标签和功能：

## Doxygen风格的头文件 (example.h)

```c
/**
 * @file example.h
 * @brief 高级用户管理系统头文件
 * 
 * @defgroup user_management 用户管理模块
 * @brief 提供完整的用户管理功能，包括创建、删除、查询和统计
 * 
 * @details
 * 本模块实现了高效的用户数据管理，支持动态内存分配和多种查询方式。
 * 采用面向对象的设计思想，提供了完整的错误处理机制。
 * 
 * @note 本模块不是线程安全的，在多线程环境中使用需要外部同步
 * @warning 使用前必须调用初始化函数，使用后必须调用清理函数
 * @bug 已知问题：在极端内存不足情况下可能无法正常处理错误
 * @todo 添加线程安全支持
 * @todo 实现用户数据持久化存储
 * 
 * @author 开发者姓名
 * @email developer@company.com
 * @date 2024-01-01
 * @version 2.1.0
 * 
 * @copyright Copyright (c) 2024 公司名称. 保留所有权利。
 * 
 * @license
 * 本项目采用MIT许可证：
 * 允许自由使用、复制、修改、合并、发布、分发、再许可和/或销售本软件的副本。
 * 
 * @par 历史记录:
 * <table>
 * <tr><th>日期         <th>版本    <th>作者        <th>描述
 * <tr><td>2024-01-01  <td>2.1.0  <td>开发者姓名  <td>添加批量操作功能
 * <tr><td>2023-12-15  <td>2.0.0  <td>开发者姓名  <td>重构为模块化设计
 * <tr><td>2023-11-01  <td>1.5.0  <td>开发者姓名  <td>添加统计功能
 * </table>
 */

#ifndef EXAMPLE_H
#define EXAMPLE_H

#ifdef __cplusplus
extern "C" {
#endif

/* ============================ 包含头文件 ============================ */

#include <stdint.h>     /**< 标准整数类型定义 */
#include <stdbool.h>    /**< 布尔类型定义 */
#include <stddef.h>     /**< 标准定义，包含size_t等 */

/* ============================ 公共常量定义 ============================ */

/**
 * @def MAX_USER_NAME_LENGTH
 * @brief 用户姓名的最大长度（包含终止符）
 * @ingroup user_management
 */
#define MAX_USER_NAME_LENGTH 64

/**
 * @def MAX_USERS
 * @brief 系统支持的最大用户数量
 * @ingroup user_management
 */
#define MAX_USERS 1000

/**
 * @def INVALID_USER_ID
 * @brief 无效用户ID常量
 * @ingroup user_management
 */
#define INVALID_USER_ID 0xFFFFFFFF

/**
 * @def USER_SYSTEM_VERSION
 * @brief 用户系统版本号字符串
 * @ingroup user_management
 */
#define USER_SYSTEM_VERSION "2.1.0"

/* ============================ 错误码枚举定义 ============================ */

/**
 * @enum user_error_t
 * @brief 用户管理模块错误码定义
 * @ingroup user_management
 * 
 * 所有函数都返回这些错误码之一，调用者应该检查返回值。
 */
typedef enum {
    USER_SUCCESS = 0,                   /**< 操作成功完成 */
    USER_ERROR_INVALID_PARAM = -1,      /**< 无效的参数 */
    USER_ERROR_NOT_FOUND = -2,          /**< 用户不存在 */
    USER_ERROR_ALREADY_EXISTS = -3,     /**< 用户已存在 */
    USER_ERROR_INSUFFICIENT_MEMORY = -4,/**< 内存不足 */
    USER_ERROR_SYSTEM_NOT_INIT = -5,    /**< 系统未初始化 */
    USER_ERROR_PERMISSION_DENIED = -6,  /**< 权限不足 */
    USER_ERROR_SYSTEM_BUSY = -7,        /**< 系统繁忙 */
    USER_ERROR_INVALID_STATE = -8,      /**< 无效的系统状态 */
    USER_ERROR_IO_ERROR = -9,           /**< 输入输出错误 */
    USER_ERROR_TIMEOUT = -10,           /**< 操作超时 */
    USER_ERROR_UNKNOWN = -127           /**< 未知错误 */
} user_error_t;

/* ============================ 数据结构定义 ============================ */

/**
 * @struct user_info_t
 * @brief 用户信息结构体
 * @ingroup user_management
 * 
 * 包含用户的完整信息，用于在系统中标识和描述用户。
 */
typedef struct {
    uint32_t id;                        /**< 用户唯一标识符 @see INVALID_USER_ID */
    char name[MAX_USER_NAME_LENGTH];    /**< 用户姓名，UTF-8编码 */
    uint8_t age;                        /**< 用户年龄，0-255 */
    uint32_t group_id;                  /**< 所属组ID */
    uint64_t create_time;               /**< 创建时间戳（Unix时间戳） */
    uint64_t last_login;                /**< 最后登录时间戳 */
    bool is_active;                     /**< 账户激活状态 */
    bool is_verified;                   /**< 账户验证状态 */
    uint8_t reserved[32];               /**< 保留字段，用于未来扩展 */
} user_info_t;

/**
 * @struct user_stats_t
 * @brief 用户统计信息结构体
 * @ingroup user_management
 * 
 * 包含用户系统的统计信息，用于监控和报告。
 */
typedef struct {
    uint32_t total_users;               /**< 用户总数 */
    uint32_t active_users;              /**< 活跃用户数 */
    uint32_t online_users;              /**< 在线用户数 */
    uint32_t max_concurrent_users;      /**< 最大并发用户数 */
    uint64_t total_logins;              /**< 总登录次数 */
    double system_uptime;               /**< 系统运行时间（秒） */
} user_stats_t;

/**
 * @struct user_filter_t
 * @brief 用户查询过滤器结构体
 * @ingroup user_management
 * 
 * 用于在查询用户时指定过滤条件。
 */
typedef struct {
    uint32_t min_age;                   /**< 最小年龄，0表示不限制 */
    uint32_t max_age;                   /**< 最大年龄，0表示不限制 */
    uint32_t group_id;                  /**< 组ID，0表示所有组 */
    bool only_active;                   /**< 是否只查询活跃用户 */
    bool only_verified;                 /**< 是否只查询已验证用户 */
} user_filter_t;

/* ============================ 回调函数类型定义 ============================ */

/**
 * @typedef user_callback_t
 * @brief 用户遍历回调函数类型
 * @ingroup user_management
 * 
 * @param[in] user 当前处理的用户信息指针
 * @param[in] context 用户上下文数据
 * @return 返回true继续遍历，false停止遍历
 * 
 * @note 回调函数中不应修改用户数据
 * @warning 回调函数执行时间应尽可能短，避免阻塞其他操作
 */
typedef bool (*user_callback_t)(const user_info_t *user, void *context);

/**
 * @typedef user_event_callback_t
 * @brief 用户事件回调函数类型
 * @ingroup user_management
 * 
 * @param[in] event_type 事件类型
 * @param[in] user_id 相关用户ID
 * @param[in] context 用户上下文数据
 */
typedef void (*user_event_callback_t)(int event_type, uint32_t user_id, void *context);

/* ============================ 全局变量声明 ============================ */

/**
 * @var g_user_system_version
 * @brief 用户系统版本字符串
 * @ingroup user_management
 * 
 * @note 只读变量，不应直接修改
 */
extern const char *g_user_system_version;

/* ============================ 函数声明 ============================ */

/** @addtogroup user_management
 *  @{
 */

/* 系统管理函数 */

/**
 * @brief 初始化用户管理系统
 * 
 * @param[in] max_users 最大用户数限制
 * @param[in] config_file 配置文件路径（可为NULL）
 * 
 * @return 错误码 @see user_error_t
 * 
 * @note 此函数必须在调用任何其他用户管理函数之前调用
 * @warning 多次调用此函数将返回USER_ERROR_INVALID_STATE
 * @see user_system_cleanup()
 * 
 * @par 示例:
 * @code
 * user_error_t ret = user_system_init(1000, "config.json");
 * if (ret != USER_SUCCESS) {
 *     // 处理错误
 * }
 * @endcode
 */
user_error_t user_system_init(uint32_t max_users, const char *config_file);

/**
 * @brief 清理用户管理系统资源
 * 
 * @return 错误码 @see user_error_t
 * 
 * @note 此函数会释放所有分配的资源，之后必须重新初始化才能使用
 * @warning 此函数调用后，所有用户数据将丢失
 * @see user_system_init()
 */
user_error_t user_system_cleanup(void);

/* 用户管理函数 */

/**
 * @brief 创建新用户
 * 
 * @param[in] name 用户姓名
 * @param[in] age 用户年龄
 * @param[in] group_id 所属组ID
 * @param[out] user_id 返回创建的用户ID
 * 
 * @return 错误码 @see user_error_t
 * 
 * @pre 系统必须已初始化
 * @post 如果成功，user_id将包含新用户的ID
 * 
 * @note 用户名会被自动修剪前后空格
 * @warning 用户名不能为空且不能超过MAX_USER_NAME_LENGTH-1个字符
 */
user_error_t user_create(const char *name, uint8_t age, uint32_t group_id, uint32_t *user_id);

/**
 * @brief 删除用户
 * 
 * @param[in] user_id 要删除的用户ID
 * 
 * @return 错误码 @see user_error_t
 * 
 * @note 此操作不可逆，用户数据将永久删除
 * @warning 删除用户时不会检查该用户是否在线
 */
user_error_t user_delete(uint32_t user_id);

/**
 * @brief 根据用户ID查找用户信息
 * 
 * @param[in] user_id 要查找的用户ID
 * @param[out] user_info 返回用户信息（可选，可为NULL）
 * 
 * @return 错误码 @see user_error_t
 * 
 * @note 如果user_info为NULL，函数只检查用户是否存在
 * @warning 返回的user_info指针在下次调用用户管理函数前有效
 */
user_error_t user_find_by_id(uint32_t user_id, user_info_t *user_info);

/**
 * @brief 根据用户名查找用户信息
 * 
 * @param[in] name 要查找的用户名
 * @param[out] user_info 返回用户信息（可选，可为NULL）
 * 
 * @return 错误码 @see user_error_t
 * 
 * @note 用户名比较不区分大小写
 * @warning 如果有多个同名用户，只返回第一个找到的
 */
user_error_t user_find_by_name(const char *name, user_info_t *user_info);

/**
 * @brief 遍历所有用户
 * 
 * @param[in] callback 每个用户调用的回调函数
 * @param[in] context 传递给回调函数的上下文数据
 * @param[in] filter 过滤条件（可选，可为NULL）
 * 
 * @return 错误码 @see user_error_t
 * 
 * @note 回调函数返回false可以提前终止遍历
 * @see user_callback_t
 */
user_error_t user_iterate(user_callback_t callback, void *context, const user_filter_t *filter);

/* 统计和监控函数 */

/**
 * @brief 获取用户系统统计信息
 * 
 * @param[out] stats 返回统计信息
 * 
 * @return 错误码 @see user_error_t
 * 
 * @note 统计信息是实时计算的，可能影响性能
 */
user_error_t user_get_stats(user_stats_t *stats);

/**
 * @brief 重置用户系统统计信息
 * 
 * @return 错误码 @see user_error_t
 * 
 * @note 只重置计数类统计，不影响用户数据
 */
user_error_t user_reset_stats(void);

/* 工具函数 */

/**
 * @brief 验证用户ID是否有效
 * 
 * @param[in] user_id 要验证的用户ID
 * 
 * @return true 用户ID有效且存在
 * @return false 用户ID无效或不存在
 * 
 * @note 此函数比user_find_by_id()更轻量
 */
bool user_is_valid_id(uint32_t user_id);

/**
 * @brief 获取用户系统版本信息
 * 
 * @return 版本字符串指针
 * 
 * @note 返回的字符串不应被修改
 * @see g_user_system_version
 */
const char* user_get_version_string(void);

/**
 * @brief 设置用户事件回调函数
 * 
 * @param[in] callback 事件回调函数
 * @param[in] context 上下文数据
 * 
 * @return 错误码 @see user_error_t
 * 
 * @note 事件包括用户创建、删除、登录、退出等
 * @see user_event_callback_t
 */
user_error_t user_set_event_callback(user_event_callback_t callback, void *context);

/** @} */ // end of user_management group

#ifdef __cplusplus
}
#endif

#endif /* EXAMPLE_H */
```

## Doxygen风格的源文件 (example.c)

```c
/**
 * @file example.c
 * @brief 高级用户管理系统实现
 * 
 * @ingroup user_management
 * 
 * @details
 * 本文件实现了用户管理系统的所有功能，包括：
 * - 系统初始化和资源管理
 * - 用户数据的增删改查
 * - 用户统计和监控
 * - 事件通知机制
 * 
 * 实现特点：
 * - 使用动态数组存储用户数据，支持自动扩容
 * - 采用LRU缓存优化频繁访问的用户
 * - 实现引用计数管理用户对象生命周期
 * 
 * @internal
 * 模块内部实现细节：
 * - 使用红黑树维护用户ID索引
 * - 使用哈希表维护用户名索引
 * - 内存分配使用自定义内存池
 * 
 * @note 性能考虑：用户数量超过10000时建议使用数据库后端
 * @warning 所有导出函数都包含参数验证，但内部函数不包含
 * 
 * @author 开发者姓名
 * @email developer@company.com
 * @date 2024-01-01
 * @version 2.1.0
 * 
 * @copyright Copyright (c) 2024 公司名称. 保留所有权利。
 */

#include "example.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

/* ============================ 模块内部常量 ============================ */

/** @def INITIAL_USER_CAPACITY
 *  @brief 用户数组初始容量
 *  @hideinitializer
 */
#define INITIAL_USER_CAPACITY 128

/** @def USER_GROWTH_FACTOR
 *  @brief 用户数组增长因子
 *  @hideinitializer
 */
#define USER_GROWTH_FACTOR 2

/** @def MAX_USERNAME_LENGTH
 *  @brief 用户名最大长度（内部使用，包含终止符）
 *  @hideinitializer
 */
#define MAX_USERNAME_LENGTH 256

/** @def USER_HASH_TABLE_SIZE
 *  @brief 用户哈希表大小
 *  @hideinitializer
 */
#define USER_HASH_TABLE_SIZE 1024

/* ============================ 模块内部数据结构 ============================ */

/**
 * @struct user_entry_t
 * @brief 用户条目内部结构
 * @private
 * 
 * 内部使用的用户数据结构，包含管理信息和用户数据。
 */
typedef struct user_entry_t {
    user_info_t info;                   /**< 用户信息 */
    uint32_t ref_count;                 /**< 引用计数 */
    struct user_entry_t *name_next;     /**< 用户名哈希表下一个节点 */
    struct user_entry_t *lru_prev;      /**< LRU缓存前一个节点 */
    struct user_entry_t *lru_next;      /**< LRU缓存下一个节点 */
} user_entry_t;

/**
 * @struct user_system_t
 * @brief 用户系统内部状态
 * @private
 * 
 * 管理整个用户系统的内部状态和数据。
 */
typedef struct {
    user_entry_t **users;               /**< 用户数组 */
    user_entry_t **name_hash;           /**< 用户名哈希表 */
    user_entry_t *lru_head;             /**< LRU链表头 */
    user_entry_t *lru_tail;             /**< LRU链表尾 */
    user_stats_t stats;                 /**< 统计信息 */
    user_event_callback_t event_cb;     /**< 事件回调函数 */
    void *event_context;                /**< 事件回调上下文 */
    uint32_t capacity;                  /**< 当前容量 */
    uint32_t count;                     /**< 当前用户数 */
    uint32_t max_users;                 /**< 最大用户数限制 */
    uint32_t next_user_id;              /**< 下一个用户ID */
    bool initialized;                   /**< 系统是否已初始化 */
    uint8_t reserved[64];               /**< 保留字段 */
} user_system_t;

/* ============================ 静态全局变量 ============================ */

/** 
 * @var g_user_system_version
 * @brief 用户系统版本字符串
 */
const char *g_user_system_version = USER_SYSTEM_VERSION;

/**
 * @var g_user_system
 * @brief 用户系统全局实例
 * @static
 * @private
 */
static user_system_t g_user_system;

/* ============================ 静态函数声明 ============================ */

/**
 * @brief 初始化用户系统内部结构
 * @private
 * 
 * @return user_error_t 错误码
 */
static user_error_t user_system_init_internal(void);

/**
 * @brief 清理用户系统内部结构
 * @private
 */
static void user_system_cleanup_internal(void);

/**
 * @brief 扩展用户数组容量
 * @private
 * 
 * @return user_error_t 错误码
 */
static user_error_t expand_user_array(void);

/**
 * @brief 计算字符串的哈希值
 * @private
 * 
 * @param[in] str 输入字符串
 * @return uint32_t 哈希值
 */
static uint32_t calculate_string_hash(const char *str);

/**
 * @brief 添加用户到哈希表
 * @private
 * 
 * @param[in] entry 用户条目
 */
static void add_user_to_hash_table(user_entry_t *entry);

/**
 * @brief 从哈希表移除用户
 * @private
 * 
 * @param[in] entry 用户条目
 */
static void remove_user_from_hash_table(user_entry_t *entry);

/**
 * @brief 在哈希表中查找用户
 * @private
 * 
 * @param[in] name 用户名
 * @return user_entry_t* 用户条目指针
 */
static user_entry_t* find_user_in_hash_table(const char *name);

/**
 * @brief 更新LRU缓存
 * @private
 * 
 * @param[in] entry 用户条目
 */
static void update_lru_cache(user_entry_t *entry);

/**
 * @brief 分配新用户条目
 * @private
 * 
 * @return user_entry_t* 用户条目指针
 */
static user_entry_t* allocate_user_entry(void);

/**
 * @brief 释放用户条目
 * @private
 * 
 * @param[in] entry 用户条目
 */
static void free_user_entry(user_entry_t *entry);

/**
 * @brief 验证用户参数
 * @private
 * 
 * @param[in] name 用户名
 * @param[in] age 年龄
 * @return user_error_t 错误码
 */
static user_error_t validate_user_params(const char *name, uint8_t age);

/**
 * @brief 触发用户事件
 * @private
 * 
 * @param[in] event_type 事件类型
 * @param[in] user_id 用户ID
 */
static void trigger_user_event(int event_type, uint32_t user_id);

/* ============================ 公共函数实现 ============================ */

user_error_t user_system_init(uint32_t max_users, const char *config_file)
{
    user_error_t ret;
    
    /* 参数验证 */
    if (max_users == 0 || max_users > MAX_USERS) {
        return USER_ERROR_INVALID_PARAM;
    }
    
    /* 检查是否已经初始化 */
    if (g_user_system.initialized) {
        return USER_ERROR_INVALID_STATE;
    }
    
    /* 初始化系统字段 */
    memset(&g_user_system, 0, sizeof(g_user_system));
    g_user_system.max_users = max_users;
    g_user_system.capacity = INITIAL_USER_CAPACITY;
    g_user_system.next_user_id = 1;
    
    /* 初始化内部结构 */
    ret = user_system_init_internal();
    if (ret != USER_SUCCESS) {
        user_system_cleanup_internal();
        return ret;
    }
    
    /* 标记为已初始化 */
    g_user_system.initialized = true;
    
    /* 记录初始化事件 */
    trigger_user_event(0, 0); /* 系统启动事件 */
    
    return USER_SUCCESS;
}

user_error_t user_system_cleanup(void)
{
    /* 检查系统状态 */
    if (!g_user_system.initialized) {
        return USER_ERROR_SYSTEM_NOT_INIT;
    }
    
    /* 触发系统关闭事件 */
    trigger_user_event(1, 0); /* 系统关闭事件 */
    
    /* 清理内部资源 */
    user_system_cleanup_internal();
    
    /* 重置系统状态 */
    memset(&g_user_system, 0, sizeof(g_user_system));
    
    return USER_SUCCESS;
}

user_error_t user_create(const char *name, uint8_t age, uint32_t group_id, uint32_t *user_id)
{
    user_error_t ret;
    user_entry_t *entry;
    
    /* 参数验证 */
    if (name == NULL || user_id == NULL) {
        return USER_ERROR_INVALID_PARAM;
    }
    
    /* 系统状态检查 */
    if (!g_user_system.initialized) {
        return USER_ERROR_SYSTEM_NOT_INIT;
    }
    
    /* 验证用户参数 */
    ret = validate_user_params(name, age);
    if (ret != USER_SUCCESS) {
        return ret;
    }
    
    /* 检查用户数量限制 */
    if (g_user_system.count >= g_user_system.max_users) {
        return USER_ERROR_INSUFFICIENT_MEMORY;
    }
    
    /* 检查用户名是否已存在 */
    if (find_user_in_hash_table(name) != NULL) {
        return USER_ERROR_ALREADY_EXISTS;
    }
    
    /* 分配用户条目 */
    entry = allocate_user_entry();
    if (entry == NULL) {
        return USER_ERROR_INSUFFICIENT_MEMORY;
    }
    
    /* 初始化用户信息 */
    entry->info.id = g_user_system.next_user_id++;
    strncpy(entry->info.name, name, MAX_USER_NAME_LENGTH - 1);
    entry->info.name[MAX_USER_NAME_LENGTH - 1] = '\0';
    entry->info.age = age;
    entry->info.group_id = group_id;
    entry->info.create_time = (uint64_t)time(NULL);
    entry->info.last_login = 0;
    entry->info.is_active = true;
    entry->info.is_verified = false;
    
    /* 添加到用户数组 */
    if (g_user_system.count >= g_user_system.capacity) {
        ret = expand_user_array();
        if (ret != USER_SUCCESS) {
            free_user_entry(entry);
            return ret;
        }
    }
    
    g_user_system.users[g_user_system.count] = entry;
    g_user_system.count++;
    
    /* 添加到哈希表 */
    add_user_to_hash_table(entry);
    
    /* 更新统计信息 */
    g_user_system.stats.total_users++;
    g_user_system.stats.active_users++;
    
    /* 返回用户ID */
    *user_id = entry->info.id;
    
    /* 触发用户创建事件 */
    trigger_user_event(2, entry->info.id); /* 用户创建事件 */
    
    return USER_SUCCESS;
}

user_error_t user_delete(uint32_t user_id)
{
    uint32_t i;
    user_entry_t *entry = NULL;
    
    /* 系统状态检查 */
    if (!g_user_system.initialized) {
        return USER_ERROR_SYSTEM_NOT_INIT;
    }
    
    /* 查找用户条目 */
    for (i = 0; i < g_user_system.count; i++) {
        if (g_user_system.users[i]->info.id == user_id) {
            entry = g_user_system.users[i];
            break;
        }
    }
    
    if (entry == NULL) {
        return USER_ERROR_NOT_FOUND;
    }
    
    /* 从哈希表移除 */
    remove_user_from_hash_table(entry);
    
    /* 从用户数组移除（将最后一个元素移动到当前位置） */
    if (i < g_user_system.count - 1) {
        g_user_system.users[i] = g_user_system.users[g_user_system.count - 1];
    }
    g_user_system.count--;
    
    /* 更新统计信息 */
    g_user_system.stats.total_users--;
    if (entry->info.is_active) {
        g_user_system.stats.active_users--;
    }
    
    /* 触发用户删除事件 */
    trigger_user_event(3, user_id); /* 用户删除事件 */
    
    /* 释放用户条目 */
    free_user_entry(entry);
    
    return USER_SUCCESS;
}

user_error_t user_find_by_id(uint32_t user_id, user_info_t *user_info)
{
    uint32_t i;
    user_entry_t *entry = NULL;
    
    /* 系统状态检查 */
    if (!g_user_system.initialized) {
        return USER_ERROR_SYSTEM_NOT_INIT;
    }
    
    /* 查找用户条目 */
    for (i = 0; i < g_user_system.count; i++) {
        if (g_user_system.users[i]->info.id == user_id) {
            entry = g_user_system.users[i];
            break;
        }
    }
    
    if (entry == NULL) {
        return USER_ERROR_NOT_FOUND;
    }
    
    /* 更新LRU缓存 */
    update_lru_cache(entry);
    
    /* 返回用户信息（如果请求） */
    if (user_info != NULL) {
        memcpy(user_info, &entry->info, sizeof(user_info_t));
    }
    
    return USER_SUCCESS;
}

user_error_t user_get_stats(user_stats_t *stats)
{
    /* 参数验证 */
    if (stats == NULL) {
        return USER_ERROR_INVALID_PARAM;
    }
    
    /* 系统状态检查 */
    if (!g_user_system.initialized) {
        return USER_ERROR_SYSTEM_NOT_INIT;
    }
    
    /* 复制统计信息 */
    memcpy(stats, &g_user_system.stats, sizeof(user_stats_t));
    
    return USER_SUCCESS;
}

bool user_is_valid_id(uint32_t user_id)
{
    uint32_t i;
    
    /* 系统状态检查 */
    if (!g_user_system.initialized) {
        return false;
    }
    
    /* 查找用户 */
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

/* ============================ 静态函数实现 ============================ */

static user_error_t user_system_init_internal(void)
{
    /* 分配用户数组 */
    g_user_system.users = (user_entry_t**)calloc(g_user_system.capacity, sizeof(user_entry_t*));
    if (g_user_system.users == NULL) {
        return USER_ERROR_INSUFFICIENT_MEMORY;
    }
    
    /* 分配哈希表 */
    g_user_system.name_hash = (user_entry_t**)calloc(USER_HASH_TABLE_SIZE, sizeof(user_entry_t*));
    if (g_user_system.name_hash == NULL) {
        free(g_user_system.users);
        g_user_system.users = NULL;
        return USER_ERROR_INSUFFICIENT_MEMORY;
    }
    
    /* 初始化统计信息 */
    memset(&g_user_system.stats, 0, sizeof(user_stats_t));
    g_user_system.stats.system_uptime = (double)time(NULL);
    
    return USER_SUCCESS;
}

static void user_system_cleanup_internal(void)
{
    uint32_t i;
    
    /* 释放所有用户条目 */
    if (g_user_system.users != NULL) {
        for (i = 0; i < g_user_system.count; i++) {
            if (g_user_system.users[i] != NULL) {
                free_user_entry(g_user_system.users[i]);
            }
        }
        free(g_user_system.users);
        g_user_system.users = NULL;
    }
    
    /* 释放哈希表 */
    if (g_user_system.name_hash != NULL) {
        free(g_user_system.name_hash);
        g_user_system.name_hash = NULL;
    }
    
    /* 重置计数器 */
    g_user_system.count = 0;
    g_user_system.capacity = 0;
}

static user_error_t expand_user_array(void)
{
    uint32_t new_capacity;
    user_entry_t **new_users;
    
    /* 计算新容量 */
    new_capacity = g_user_system.capacity * USER_GROWTH_FACTOR;
    if (new_capacity > g_user_system.max_users) {
        new_capacity = g_user_system.max_users;
    }
    
    /* 重新分配用户数组 */
    new_users = (user_entry_t**)realloc(g_user_system.users, new_capacity * sizeof(user_entry_t*));
    if (new_users == NULL) {
        return USER_ERROR_INSUFFICIENT_MEMORY;
    }
    
    /* 更新系统状态 */
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

/* 其余静态函数实现... */

/**
 * @brief 模块自测试函数
 * @private
 * 
 * 用于单元测试的内部函数。
 * 
 * @return user_error_t 测试结果
 */
static user_error_t user_self_test(void)
{
    /* 自测试实现 */
    return USER_SUCCESS;
}

/* ============================ 单元测试支持 ============================ */

#ifdef UNIT_TEST

/**
 * @test 用户系统基础测试
 * 
 * 测试用户系统初始化和基本功能。
 */
void test_user_system_basic(void)
{
    user_error_t ret;
    uint32_t user_id;
    
    /* 测试初始化 */
    ret = user_system_init(100, NULL);
    assert(ret == USER_SUCCESS);
    
    /* 测试用户创建 */
    ret = user_create("testuser", 25, 1, &user_id);
    assert(ret == USER_SUCCESS);
    assert(user_id != INVALID_USER_ID);
    
    /* 测试用户查找 */
    user_info_t info;
    ret = user_find_by_id(user_id, &info);
    assert(ret == USER_SUCCESS);
    assert(strcmp(info.name, "testuser") == 0);
    
    /* 测试用户删除 */
    ret = user_delete(user_id);
    assert(ret == USER_SUCCESS);
    
    /* 测试清理 */
    ret = user_system_cleanup();
    assert(ret == USER_SUCCESS);
}

/**
 * @test 用户参数验证测试
 * 
 * 测试各种边界条件下的参数验证。
 */
void test_user_parameter_validation(void)
{
    user_error_t ret;
    uint32_t user_id;
    
    ret = user_system_init(10, NULL);
    assert(ret == USER_SUCCESS);
    
    /* 测试空用户名 */
    ret = user_create("", 25, 1, &user_id);
    assert(ret == USER_ERROR_INVALID_PARAM);
    
    /* 测试超长用户名 */
    char long_name[MAX_USER_NAME_LENGTH + 10];
    memset(long_name, 'A', sizeof(long_name) - 1);
    long_name[sizeof(long_name) - 1] = '\0';
    ret = user_create(long_name, 25, 1, &user_id);
    assert(ret == USER_ERROR_INVALID_PARAM);
    
    user_system_cleanup();
}

#endif /* UNIT_TEST */
```

这两个文件展示了Doxygen注释的完整功能集，包括：

## 包含的Doxygen功能：

### 基本标签：
- `@file` - 文件描述
- `@brief` - 简要描述
- `@details` - 详细描述
- `@author` - 作者信息
- `@date` - 日期
- `@version` - 版本号
- `@copyright` - 版权信息

### 分组和组织：
- `@defgroup` - 定义模块分组
- `@addtogroup` - 添加到分组
- `@{` / `@}` - 分组范围

### 函数文档：
- `@param` - 参数描述（支持[in]/[out]/[in,out]）
- `@return` - 返回值描述
- `@note` - 注意事项
- `@warning` - 警告信息
- `@pre` - 前置条件
- `@post` - 后置条件
- `@see` - 参考链接
- `@par` - 段落说明
- `@code` / `@endcode` - 代码示例

### 特殊标签：
- `@bug` - 已知问题
- `@todo` - 待办事项
- `@internal` - 内部实现说明
- `@private` - 私有成员
- `@test` - 测试用例
- `@hideinitializer` - 隐藏初始化器

### 其他功能：
- 表格支持
- 列表支持
- 条件编译文档
- 交叉引用
- 版本历史

这种详细的注释风格可以生成完整的API文档，便于团队协作和代码维护。
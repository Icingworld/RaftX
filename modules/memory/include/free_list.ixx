export module memory.free_list;

import std;

export namespace raftx::memory
{

/**
 * @brief 空闲内存块
 */
class FreeBlock
{
public:
    FreeBlock() noexcept;

    /**
     * @brief 构造空闲内存块
     * @param next 下一个空闲内存块
     */
    explicit FreeBlock(FreeBlock * next) noexcept;

    ~FreeBlock() = default;

public:
    /**
     * @brief 设置下一个空闲内存块
     * @param next 下一个空闲内存块
     */
    void set_next(FreeBlock * next) noexcept;

    /**
     * @brief 获取下一个空闲内存块
     * @return 下一个空闲内存块
     */
    [[nodiscard]] FreeBlock * next() const noexcept;

private:
    FreeBlock * next_;  // 下一个空闲内存块
};

/**
 * @brief 空闲内存块链表迭代器
 */
class FreeListIterator
{
public:
    /**
     * @brief 构造迭代器
     * @param block 当前空闲内存块
     */
    explicit FreeListIterator(FreeBlock * block) noexcept;

    ~FreeListIterator() = default;

public:
    /**
     * @brief 解引用迭代器
     * @return 当前空闲内存块
     */
    FreeBlock * operator*() const noexcept;

    /**
     * @brief 解引用迭代器
     * @return 当前空闲内存块
     */
    FreeBlock * operator->() const noexcept;

    /**
     * @brief 前置自增迭代器
     * @return 自增后的迭代器
     */
    FreeListIterator & operator++() noexcept;

    /**
     * @brief 后置自增迭代器
     * @return 自增前的迭代器
     */
    FreeListIterator operator++(int) noexcept;

    /**
     * @brief 判断两个迭代器是否相等
     * @param other 另一个迭代器
     * @return 是否相等
     */
    bool operator==(const FreeListIterator & other) const noexcept;

    /**
     * @brief 判断两个迭代器是否不相等
     * @param other 另一个迭代器
     * @return 是否不相等
     */
    bool operator!=(const FreeListIterator & other) const noexcept;

private:
    FreeBlock * block_;  // 当前空闲内存块
};

/**
 * @brief 空闲内存块链表
 */
class FreeList
{
public:
    using iterator = FreeListIterator;
    using const_iterator = const FreeListIterator;

public:
    FreeList() noexcept;

    ~FreeList() = default;

public:
    /**
     * @brief 获取空闲内存块链表的第一个空闲内存块
     * @return 第一个空闲内存块
     */
    FreeBlock * front() noexcept;

    /**
     * @brief 插入空闲内存块到空闲内存块链表的第一个位置
     * @param block 空闲内存块
     */
    void push_front(FreeBlock * block) noexcept;

    /**
     * @brief 弹出空闲内存块链表的第一个空闲内存块
     */
    void pop_front();

    /**
     * @brief 获取空闲内存块链表的迭代器
     * @return 空闲内存块链表的迭代器
     */
    iterator begin() noexcept;

    /**
     * @brief 获取空闲内存块链表的结束迭代器
     * @return 空闲内存块链表的结束迭代器
     */
    iterator end() noexcept;
    
    /**
     * @brief 获取空闲内存块链表的常量迭代器
     * @return 空闲内存块链表的常量迭代器
     */
    [[nodiscard]] const_iterator cbegin() const noexcept;

    /**
     * @brief 获取空闲内存块链表的常量结束迭代器
     * @return 空闲内存块链表的常量结束迭代器
     */
    [[nodiscard]] const_iterator cend() const noexcept;

    /**
     * @brief 判断空闲内存块链表是否为空
     * @return 是否为空
     */
    [[nodiscard]] bool empty() const noexcept;

    /**
     * @brief 获取空闲内存块链表的大小
     * @return 空闲内存块链表的大小
     */
    [[nodiscard]] std::size_t size() const noexcept;

    /**
     * @brief 清空空闲内存块链表
     */
    void clear() noexcept;

private:
    FreeBlock * head_;  // 空闲内存块链表的头节点
    std::size_t size_;  // 空闲内存块链表的大小
};

}  // namespace raftx::memory

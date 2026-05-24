module memory.free_list;

import std;

namespace raftx::memory
{

FreeBlock::FreeBlock() noexcept
    : next_(nullptr)
{
}

FreeBlock::FreeBlock(FreeBlock * next) noexcept
    : next_(next)
{
}

void FreeBlock::set_next(FreeBlock * next) noexcept
{
    next_ = next;
}

FreeBlock * FreeBlock::next() const noexcept
{
    return next_;
}

FreeListIterator::FreeListIterator(FreeBlock * block) noexcept
    : block_(block)
{
}

FreeBlock * FreeListIterator::operator*() const noexcept
{
    return block_;
}

FreeBlock * FreeListIterator::operator->() const noexcept
{
    return block_;
}

FreeListIterator & FreeListIterator::operator++() noexcept
{
    block_ = block_->next();
    return *this;
}

FreeListIterator FreeListIterator::operator++(int) noexcept
{
    FreeListIterator tmp(*this);
    ++(*this);
    return tmp;
}

bool FreeListIterator::operator==(const FreeListIterator & other) const noexcept
{
    return block_ == other.block_;
}

bool FreeListIterator::operator!=(const FreeListIterator & other) const noexcept
{
    return block_ != other.block_;
}

FreeList::FreeList() noexcept
    : head_(nullptr)
    , size_(0)
{
}

FreeBlock * FreeList::front() noexcept
{
    return head_;
}

void FreeList::push_front(FreeBlock * block) noexcept
{
    block->set_next(head_);
    head_ = block;
    ++size_;
}

void FreeList::pop_front()
{
    if (head_ != nullptr) {
        head_ = head_->next();
        --size_;
    } else {
        throw std::runtime_error("FreeList is empty");
    }
}

FreeListIterator FreeList::begin() noexcept
{
    return FreeListIterator(head_);
}

FreeListIterator FreeList::end() noexcept
{
    return FreeListIterator(nullptr);
}

FreeList::const_iterator FreeList::cbegin() const noexcept
{
    return FreeListIterator(head_);
}

FreeList::const_iterator FreeList::cend() const noexcept
{
    return FreeListIterator(nullptr);
}

bool FreeList::empty() const noexcept
{
    return head_ == nullptr;
}

std::size_t FreeList::size() const noexcept
{
    return size_;
}

void FreeList::clear() noexcept
{
    head_ = nullptr;
    size_ = 0;
}

}  // namespace raftx::memory

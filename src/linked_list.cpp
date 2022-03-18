#include "assignment/linked_list.hpp"

namespace assignment {

  LinkedList::~LinkedList() {

    // эквивалентно очистке списка
    LinkedList::Clear();
  }

  void LinkedList::Add(int value) {
    Node* n = new Node(value);
    if (size_ == 0) {
      front_ = n;
    } else {
      back_->next = n;
    }
    back_ = n;
    size_++;
  }

  bool LinkedList::Insert(int index, int value) {
    if (index > size_ || index < 0) {
      return false;
    } else {
      Node* prev_node = front_;
      Node* node_to_insert = new Node(value);
      if (index == 0) {
        node_to_insert->next = prev_node;
        front_ = node_to_insert;
        front_->next = prev_node;
        back_ = front_;
        size_++;
        return true;
      } else if (index == size_) {
        prev_node = back_;
        prev_node->next = node_to_insert;
        back_ = node_to_insert;
        size_++;
        return true;
      } else {
        for (int i = 0; i < index-1; i++) {
          prev_node = prev_node->next;
        }
        node_to_insert->next = prev_node->next;
        prev_node->next = node_to_insert;
        size_++;
        return true;
      }
    }
  }

  bool LinkedList::Set(int index, int new_value) {
    if (index+1 > size_ || index < 0 || size_ == 0) {
      return false;
    } else {
      Node* node = front_;
      for (int i = 0; i < index; i++) {
        node = node->next;
      }
      node->value = new_value;
      return true;
    }
  }

  std::optional<int> LinkedList::Remove(int index) {
    if (index >= size_ || index < 0) {
      return std::nullopt;
    } else {
      Node* prev_node = front_;
      Node* to_delete_node;
      Node* next_node;
      int value_deleted;
      if (index == 0) {
        value_deleted = front_->value;
        next_node = front_->next;
        front_ = next_node;
        size_--;
        return value_deleted;
      } else {
        for (int i = 0; i < index - 1; i++) {
          prev_node = prev_node->next;
        }
        to_delete_node = prev_node->next;
        value_deleted = to_delete_node->value;
        prev_node->next = to_delete_node->next;
        size_--;
        return value_deleted;
      }
    }
  }

  void LinkedList::Clear() {
    size_ = 0;
    front_ = nullptr;
    back_ = nullptr;
  }

  std::optional<int> LinkedList::Get(int index) const {
    if (index >= size_ || index < 0 || size_ == 0) {
      return std::nullopt;
    } else {
      Node* node = front_;
      for (int i = 0; i < index; i++) {
        node = node->next;
      }
      return node->value;
    }
  }

  std::optional<int> LinkedList::IndexOf(int value) const {
    Node* node = front_;
    for (int i = 0; i < size_; i++) {
      if (node->value == value) {
        return i;
      }
      node = node->next;
    }
    return std::nullopt;
  }

  bool LinkedList::Contains(int value) const {
    Node* node = front_;
    for (int i = 0; i < size_; i++) {
      if (node->value == value) {
        return true;
      }
      node = node->next;
    }
    return false;
  }

  bool LinkedList::IsEmpty() const {
    return size_ == 0;
  }

  int LinkedList::size() const {
    return size_;
  }

  std::optional<int> LinkedList::front() const {
    if (size_ == 0) {
      return std::nullopt;
    } else {
      return front_->value;
    }
  }

  std::optional<int> LinkedList::back() const {
    if (size_ == 0) {
      return std::nullopt;
    } else {
      return back_->value;
    }
  }

  Node* LinkedList::FindNode(int index) const {
    if (index+1 > size_ || index < 0 || size_ == 0) {
      return nullptr;
    } else {
      Node* node = front_;
      for (int i = 0; i < index; i++) {
        node = node->next;
      }
      return node;
    }
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  LinkedList::LinkedList(const std::vector<int>& values) {

    if (values.empty()) {
      return;
    }

    auto* curr_node = new Node(values.front());
    front_ = curr_node;

    for (int index = 1; index < values.size() - 1; ++index) {
      curr_node->next = new Node(values[index]);
      curr_node = curr_node->next;
    }

    if (values.size() == 1) {
      back_ = front_;
    } else {
      curr_node->next = new Node(values.back());
      back_ = curr_node->next;
    }

    size_ = static_cast<int>(values.size());
  }

  std::vector<int> LinkedList::toVector() const {

    if (front_ == nullptr || size_ == 0) {
      return {};
    }

    std::vector<int> array;
    array.reserve(size_);

    for (auto* node = front_; node != nullptr; node = node->next) {
      array.push_back(node->value);
    }

    return array;
  }

}  // namespace assignment
#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <random>

template<typename Key, typename Value, template<typename...> class Container = std::list>
class UnorderedMap {
	struct Pair {
		Key key;
		Value value;
		Pair() : key(), value() {};
		Pair(const Key& key, const Value& value) : key(key), value(value) {};
	};
	std::vector<Container<Pair>> _data;
	size_t _size;

	size_t hash(const Key& key) const { //деления ключа на размер таблицы
		return key % _data.size();
	}

	void grow() {
		std::vector<Container<Pair>> new_data;
		new_data.resize(_data.size() * 1.7);
		_size = 0;
		std::swap(new_data, _data);
		for (size_t i = 0; i < new_data.size(); ++i) {
			for (auto& pair : new_data[i]) {
				insert(pair.key, pair.value);
			}
		}
	}
public:
	UnorderedMap(const size_t size) {
		if (size == 0)
			throw std::invalid_argument("Size = 0");
		_size = 0;
		_data.resize(size);
	}
	UnorderedMap(const size_t size, const Key& key_min, const Key& key_max, const size_t min_value_len, const size_t max_value_len) {
		if (size == 0)
			throw std::invalid_argument("Size = 0");

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<Key> key_dist(key_min, key_max);

		_size = 0;
		_data.resize(size);

		for (size_t i = 0; i < size; ++i) {
			Key random_key = key_dist(gen);
			size_t len = std::uniform_int_distribution<size_t>(min_value_len, max_value_len)(gen);
			std::string random_value;
			random_value.reserve(len);
			for (size_t j = 0; j < len; ++j) {
				random_value += 'A' + (rand() % 26);
			}
			insert(random_key, random_value);
		}
	}
	UnorderedMap(const UnorderedMap& other): _size(other._size), _data(other._data) {}
	~UnorderedMap() = default;
	UnorderedMap& operator=(const UnorderedMap& other) {
		UnorderedMap copy(other);
		if (this != &copy) {
			std::swap(*this, copy);
		}
		return *this;
	}

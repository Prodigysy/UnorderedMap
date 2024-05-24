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

	void print() const {
		size_t i = 0;
		std::cout << "HashTable:" << std::endl;
		for (auto& list : _data) {
			std::cout << "Bucket " << i++ << ": ";
			for (auto& pair : list) {
				std::cout << "{" << pair.key << ": " << pair.value << "} ";
			}
			std::cout << std::endl;
		}
	}
	void insert(const Key& key, const Value& value) {
		double load_factor = _size / (_data.size() + 0.0);
		if (load_factor > 0.6) grow();
		size_t idx = hash(key);
		_data[idx].emplace_back(key, value);
		++_size;
	}
	void insert_or_assign(const Key& key, const Value& value) {
		auto result = search(key);
		if (!result) {
			insert(key, value);
			return;
		}
		*result = value;
	}
	bool contains(const Value& value) {
		for (auto& list : _data) {
			for (auto& pair : list) {
				if (pair.value == value)
					return true;
			}
		}
		return false;
	}
	Value* search(const Key& key) {
		size_t idx = hash(key);
		for (auto& pair : _data[idx]) {	
			if (pair.key == key)
				return &pair.value;
		}
		return nullptr;
	}
	bool erase(const Key& key) {
		size_t idx = hash(key);
		auto& list = _data[idx];
		for (auto it = list.begin(); it != list.end(); ++it) {
			if (it->key == key) {
				list.erase(it);
				--_size;
				return true;
			}
		}
		return false;
	}
	int count(const Key& key) {
		int count = 0;
		size_t idx = hash(key);
		for (auto& pair : _data[idx]) {
			if (pair.key == key) ++count;
		}
		return count;
	}
};
int romanHash(const char& roman) {
	switch (roman) {
	case 'I': return 1;
	case 'V': return 5;
	case 'X': return 10;
	case 'L': return 50;
	case 'C': return 100;
	case 'D': return 500;
	case 'M': return 1000;
	default: return -1;
	}
}
int romanToDecimal(const std::string& roman) {
	UnorderedMap<char, int> romanMap(7);
	for (const char& c : roman) {
		romanMap.insert(c, romanHash(c));
	}

	int decimal = 0;
	int prevValue = 0;

	for (size_t i = 0; i < roman.size(); ++i) {
		int value = *romanMap.search(roman[i]);
		decimal += value;

		if (value > prevValue) {
			decimal -= 2 * prevValue;
		}

		prevValue = value;
	}

	return decimal;
}
#pragma once
template <typename TKey, typename TValue>
class AssociativeContainer
{
public:
	virtual void incert(const TKey& key, const TValue& value) = 0;
	virtual TValue& find(const TKey& key) const = 0;
	virtual void remove(const TKey& key) = 0;
};


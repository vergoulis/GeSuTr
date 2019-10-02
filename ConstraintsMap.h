//
// Created by serafeim on 2/10/2019.
//

#ifndef MPPAGERANK_CONSTRAINTSMAP_H
#define MPPAGERANK_CONSTRAINTSMAP_H

#include <unordered_map>

typedef std::tuple<string, string, string> c_key;

struct key_hash : public std::unary_function<c_key, std::size_t>
{
    std::size_t operator()(const c_key& k) const
    {
        hash<string> hasher;
        return hasher(std::get<0>(k)) ^ hasher(std::get<1>(k)) ^ hasher(std::get<2>(k));
    }
};

struct key_equal : public std::binary_function<c_key, c_key, bool>
{
    bool operator()(const c_key& v0, const c_key& v1) const
    {
        return (
                std::get<0>(v0) == std::get<0>(v1) &&
                std::get<1>(v0) == std::get<1>(v1) &&
                std::get<2>(v0) == std::get<2>(v1)
        );
    }
};

typedef std::unordered_map<const c_key, TransitionMatrix*, key_hash, key_equal> c_map;


#endif //MPPAGERANK_CONSTRAINTSMAP_H

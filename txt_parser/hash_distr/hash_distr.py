import sys
from collections import defaultdict
import matplotlib.pyplot as plt
import hashlib
import zlib

def build_distribution(file_path, hash_func, num_buckets=32768):
    bucket_counts = defaultdict(int)

    with open(file_path, 'r', encoding='utf-8') as f:
        f = set(f)
        for word in f:
            if word:
                bucket_index = hash_func(word) % num_buckets
                bucket_counts[bucket_index] += 1

    full_distribution = [0] * num_buckets
    for i in range(num_buckets):
        full_distribution[i] = bucket_counts[i]
    print(max(full_distribution))

    return full_distribution

def plot_distribution(distribution):
    distribution = distribution[:4096]
    plt.figure(figsize=(12, 6))
    plt.bar(range(len(distribution)), distribution, width=1.0)
    plt.xlabel('Bucket Index')
    plt.ylabel('Words per Bucket')
    plt.title('Hash Distribution of Words')
    plt.tight_layout()
    plt.savefig("txt_parser/hash_distr/sum_ascii_hash.png")
    # plt.show()


def sha256_hash(word):
    return int(hashlib.sha256(word.encode('utf-8')).hexdigest(), 16)


def sum_ascii_hash(word):
    return sum(list(map(ord, list(word))))

def length_hash(word):
    return len(word)

def zero_hash(word):
    return 0

def crc32_hash(word):
    return zlib.crc32(word.encode('utf-8'))

file_path = 'txt_parser/war_and_peace_words.txt'
distribution = build_distribution(file_path, sum_ascii_hash)
plot_distribution(distribution)

<?php

/**
 * @generate-class-entries
 * @generate-legacy-arginfo 70000
 */

class BitSet {

	public function __construct(int $value=0) {}

	public function andOp(BitSet $set): void {}

	public function andNotOp(BitSet $set): void {}

	public function cardinality(): int {}

	public function clear(int $from=-1, int $to=0): void {}

	static public function fromArray(array $arr): BitSet {}

	static public function fromInteger(int $value): BitSet {}

	static public function fromString(string $str): BitSet {}

	static public function fromRawValue(string $str): BitSet {}

	public function get(int $index): bool {}

	public function getRawValue(): string {}

	public function intersects(BitSet $set): bool {}

	public function isEmpty(): bool {}

	public function length(): int {}

	public function nextClearBit(int $start): bool|int {}

	public function nextSetBit(int $start): bool|int {}

	public function orOp(BitSet $set): void {}

	public function previousClearBit(int $start): bool|int {}

	public function previousSetBit(int $start): bool|int {}

	public function set(int $from=-1, int $to=0): void {}

	public function size(): int {}

	public function toArray(): array {}

	public function toInteger(): int {}

	public function xorOp(BitSet $set): void {}

	public function __toString(): string {}
}

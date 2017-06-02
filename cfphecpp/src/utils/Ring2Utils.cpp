#include "Ring2Utils.h"

//---------------------------------

void Ring2Utils::add(ZZX& res, ZZX& p1, ZZX& p2, ZZ& mod, const long& degree) {
	res.SetLength(degree);
	for (long i = 0; i < degree; ++i) {
		AddMod(res.rep[i], p1.rep[i], p2.rep[i], mod);
	}
	res.normalize();
}

void Ring2Utils::add(CZZX& res, CZZX& p1, CZZX& p2, ZZ& mod, const long& degree) {
	add(res.rx, p1.rx, p2.rx, mod, degree);
	add(res.ix, p1.ix, p2.ix, mod, degree);
}

void Ring2Utils::addAndEqual(ZZX& p1, ZZX& p2, ZZ& mod, const long& degree) {
	for (long i = 0; i < degree; ++i) {
		AddMod(p1.rep[i], p1.rep[i], p2.rep[i], mod);
	}
	p1.normalize();
}

void Ring2Utils::addAndEqual(CZZX& p1, CZZX& p2, ZZ& mod, const long& degree) {
	addAndEqual(p1.rx, p2.rx, mod, degree);
	addAndEqual(p1.ix, p2.ix, mod, degree);
}

void Ring2Utils::average(ZZX& res, ZZX*& ps, long& size, ZZ& mod, const long& degree) {
	res.SetLength(degree);
	for (long i = 0; i < degree; ++i) {
		ZZ tmp = ZZ::zero();
		for (long j = 0; j < size; ++j) {
			tmp += ps[j].rep[i];
		}
		res.rep[i] = tmp / size;
		res.rep[i] %= mod;
	}
	res.normalize();
}

//-----------------------------------------

void Ring2Utils::sub(ZZX& res, ZZX& p1, ZZX& p2, ZZ& mod, const long& degree) {
	res.SetLength(degree);
	for (long i = 0; i < degree; ++i) {
		AddMod(res.rep[i], p1.rep[i], -p2.rep[i], mod);
	}
	res.normalize();
}

void Ring2Utils::sub(CZZX& res, CZZX& p1, CZZX& p2, ZZ& mod, const long& degree) {
	sub(res.rx, p1.rx, p2.rx, mod, degree);
	sub(res.ix, p1.ix, p2.ix, mod, degree);
}

void Ring2Utils::subAndEqual(ZZX& p1, ZZX& p2, ZZ& mod, const long& degree) {
	for (long i = 0; i < degree; ++i) {
		AddMod(p1.rep[i], p1.rep[i], -p2.rep[i], mod);
	}
	p1.normalize();
}

void Ring2Utils::subAndEqual(CZZX& p1, CZZX& p2, ZZ& mod, const long& degree) {
	subAndEqual(p1.rx, p2.rx, mod, degree);
	subAndEqual(p1.ix, p2.ix, mod, degree);
}

//-----------------------------------------

void Ring2Utils::mult(ZZX& res, ZZX& p1, ZZX& p2, ZZ& mod, const long& degree) {
	ZZ tmp1, tmp2;
	ZZX p;
	p.SetLength(2 * degree);
	res.SetLength(degree);
	mul(p, p1, p2);

	for (long i = 0; i < degree; ++i) {
		tmp1 = coeff(p, i);
		tmp2 = coeff(p, i + degree);
		tmp1 %= mod;
		tmp2 %= mod;
		tmp2 = mod - tmp2;
		AddMod(res.rep[i], tmp1, tmp2, mod);
	}
	res.normalize();
}

void Ring2Utils::mult(CZZX& res, CZZX& p1, CZZX& p2, ZZ& mod, const long& degree) {
	ZZX tmp1, tmp2, tmp3;

	add(tmp1, p1.rx, p1.ix, mod, degree);
	multAndEqual(tmp1, p2.rx, mod, degree);

	add(tmp2, p2.rx, p2.ix, mod, degree);
	multAndEqual(tmp2, p1.ix, mod, degree);
	sub(res.rx, tmp1, tmp2, mod, degree);

	sub(tmp2, p2.ix, p2.rx, mod, degree);
	multAndEqual(tmp2, p1.rx, mod, degree);
	add(res.ix, tmp1, tmp2, mod, degree);
}

void Ring2Utils::mult(CZZX& res, CZZX& p1, ZZX& p2, ZZ& mod, const long& degree) {
	mult(res.rx, p1.rx, p2, mod, degree);
	mult(res.ix, p1.ix, p2, mod, degree);
}

void Ring2Utils::multAndEqual(ZZX& p1, ZZX& p2, ZZ& mod, const long& degree) {
	ZZX p;
	p.SetLength(2 * degree);
	p = p1 * p2;

	for (long i = 0; i < degree; ++i) {
		p.rep[i] %= mod;
		p.rep[i + degree] %= mod;
		AddMod(p1.rep[i], p.rep[i], -p.rep[i + degree], mod);
	}
	p1.normalize();
}

void Ring2Utils::multAndEqual(CZZX& p1, CZZX& p2, ZZ& mod, const long& degree) {
	ZZX tmp1, tmp2, tmp3;

	add(tmp1, p1.rx, p1.ix, mod, degree);
	multAndEqual(tmp1, p2.rx, mod, degree);

	add(tmp2, p2.rx, p2.ix, mod, degree);
	multAndEqual(tmp2, p1.ix, mod, degree);

	sub(tmp3, p2.ix, p2.rx, mod, degree);
	multAndEqual(tmp3, p1.rx, mod, degree);

	sub(p1.rx, tmp1, tmp2, mod, degree);
	add(p2.ix, tmp1, tmp3, mod, degree);
}

void Ring2Utils::multAndEqual(CZZX& p1, ZZX& p2, ZZ& mod, const long& degree) {
	multAndEqual(p1.rx, p2, mod, degree);
	multAndEqual(p1.ix, p2, mod, degree);
}

//-----------------------------------------

void Ring2Utils::square(ZZX& res, ZZX& p, ZZ& mod, const long& degree) {
	ZZ tmp1, tmp2;
	res.SetLength(degree);
	ZZX p2;
	p2.SetLength(2 * degree);
	p2 = p * p;

	for (long i = 0; i < degree; ++i) {
		tmp1 = coeff(p2, i);
		tmp2 = coeff(p2, i + degree);
		tmp1 %= mod;
		tmp2 %= mod;
		AddMod(res.rep[i], tmp1, -tmp2, mod);
	}
	res.normalize();
}

void Ring2Utils::square(CZZX& res, CZZX& p, ZZ& mod, const long& degree) {
	ZZX tmp1, tmp2;

	add(tmp1, p.rx, p.ix, mod, degree);
	sub(tmp2, p.rx, p.ix, mod, degree);
	mult(res.rx, tmp1, tmp2, mod, degree);
	mult(tmp2, p.rx, p.ix, mod, degree);
	add(res.ix, tmp2, tmp2, mod, degree);
}

void Ring2Utils::squareAndEqual(ZZX& p, ZZ& mod, const long& degree) {
	ZZX p2;
	p2.SetLength(2 * degree);
	p2 = p * p;

	for (long i = 0; i < degree; ++i) {
		p2.rep[i] %= mod;
		p2.rep[i + degree] %= mod;
		AddMod(p.rep[i], p2.rep[i], -p2.rep[i + degree], mod);
	}
	p.normalize();
}

void Ring2Utils::squareAndEqual(CZZX& p, ZZ& mod, const long& degree) {
	ZZX tmp1, tmp2;

	add(tmp1, p.rx, p.ix, mod, degree);
	sub(tmp2, p.rx, p.ix, mod, degree);

	mult(p.rx, tmp1, tmp2, mod, degree);
	multAndEqual(p.ix, p.rx, mod, degree);
	addAndEqual(p.ix, p.ix, mod, degree);
}

//-----------------------------------------

void Ring2Utils::multByMonomial(ZZX& res, ZZX& p, const long& monomialDeg, const long& degree) {
	long shift = monomialDeg % (2 * degree);
	if(shift == 0) {
		res = p;
	}
	ZZX tmpx;
	tmpx.SetLength(degree);
	tmpx = (shift < degree) ? p : -p;
	shift %= degree;

	res.SetLength(degree);

	for (long i = 0; i < shift; ++i) {
		res.rep[i] = tmpx.rep[degree - shift + i];
	}

	for (long i = shift; i < degree; ++i) {
		res.rep[i] = tmpx.rep[i - shift];
	}
	res.normalize();
}

void Ring2Utils::multByMonomial(CZZX& res, CZZX& p, const long& monomialDeg, const long& degree) {
	multByMonomial(res.rx, p.rx, monomialDeg, degree);
	multByMonomial(res.ix, p.ix, monomialDeg, degree);
}

void Ring2Utils::multByMonomialAndEqual(ZZX& p, const long& monomialDeg, const long& degree) {
	long shift = monomialDeg % (2 * degree);
	if(shift == 0) {
		return;
	}
	ZZX tmpx;
	tmpx.SetLength(degree);
	tmpx = (shift < degree) ? p : -p;
	shift %= degree;
	for (long i = 0; i < shift; ++i) {
		p.rep[i] = -tmpx.rep[degree - shift + i];
	}

	for (long i = shift; i < degree; ++i) {
		p.rep[i] = tmpx.rep[i - shift];
	}
	p.normalize();
}

void Ring2Utils::multByMonomialAndEqual(CZZX& p, const long& monomialDeg, const long& degree) {
	multByMonomialAndEqual(p.rx, monomialDeg, degree);
	multByMonomialAndEqual(p.ix, monomialDeg, degree);
}

//-----------------------------------------

void Ring2Utils::multByConst(ZZX& res, ZZX& p, const ZZ& cnst, ZZ& mod, const long& degree) {
	res.SetLength(degree);
	for (long i = 0; i < degree; ++i) {
		MulMod(res.rep[i], p.rep[i], cnst, mod);
	}
	res.normalize();
}

void Ring2Utils::multByConst(CZZX& res, CZZX& p, const ZZ& cnst, ZZ& mod, const long& degree) {
	multByConst(res.rx, p.rx, cnst, mod, degree);
	multByConst(res.ix, p.ix, cnst, mod, degree);
}

void Ring2Utils::multByConst(CZZX& res, CZZX& p, const CZZ& cnst, ZZ& mod, const long& degree) {
	ZZX tmp1, tmp2, tmp3, tmp4;

	add(tmp1, p.rx, p.ix, mod, degree);
	multByConst(tmp2, tmp1, cnst.r, mod, degree);

	ZZ tmp = cnst.r + cnst.i;
	multByConst(tmp4, p.ix, tmp, mod, degree);

	tmp = cnst.i - cnst.r;
	multByConst(tmp3, p.rx, tmp, mod, degree);

	sub(res.rx, tmp2, tmp4, mod, degree);
	add(res.ix, tmp2, tmp3, mod, degree);
}

void Ring2Utils::multByConstAndEqual(ZZX& p, const ZZ& cnst, ZZ& mod, const long& degree) {
	for (long i = 0; i < degree; ++i) {
		MulMod(p.rep[i], p.rep[i], cnst, mod);
	}
	p.normalize();
}

void Ring2Utils::multByConstAndEqual(CZZX& p, const ZZ& cnst, ZZ& mod, const long& degree) {
	multByConstAndEqual(p.rx, cnst, mod, degree);
	multByConstAndEqual(p.ix, cnst, mod, degree);
}

void Ring2Utils::multByConstAndEqual(CZZX& p, const CZZ& cnst, ZZ& mod, const long& degree) {
	ZZX tmp1, tmp2, tmp3;
	ZZ tmp;
	add(tmp1, p.rx, p.ix, mod, degree);
	multByConstAndEqual(tmp1, cnst.r, mod, degree);

	tmp = cnst.r + cnst.i;
	multByConst(tmp2, p.ix, tmp, mod, degree);

	tmp = cnst.i - cnst.r;
	multByConst(tmp3, p.rx, tmp, mod, degree);

	sub(p.rx, tmp1, tmp2, mod, degree);
	add(p.ix, tmp1, tmp3, mod, degree);
}

//-----------------------------------------

void Ring2Utils::leftShift(ZZX& res, ZZX& p, const long& bits, const long& logMod, const long& degree) {
	ZZ c;
	res.SetLength(degree);
	for (long i = 0; i < degree; ++i) {
		c = p.rep[i] << bits;
		truncate(c, logMod);
		res.rep[i] = c;
	}
	res.normalize();
}

void Ring2Utils::leftShift(CZZX& res, CZZX& p, const long& bits, const long& logMod, const long& degree) {
	leftShift(res.rx, p.rx, bits, logMod, degree);
	leftShift(res.ix, p.ix, bits, logMod, degree);
}

void Ring2Utils::leftShiftAndEqual(ZZX& p, const long& bits, const long& logMod, const long& degree) {
	for (long i = 0; i < degree; ++i) {
		truncate(p.rep[i], logMod - bits);
		p.rep[i] <<= bits;
	}
	p.normalize();
}

void Ring2Utils::leftShiftAndEqual(CZZX& p, const long& bits, const long& logMod, const long& degree) {
	leftShiftAndEqual(p.rx, bits, logMod, degree);
	leftShiftAndEqual(p.ix, bits, logMod, degree);
}

//-----------------------------------------

void Ring2Utils::rightShift(ZZX& res, ZZX& p, const long& bits, const long& logMod, const long& degree) {
	ZZ c;
	res.SetLength(degree);
	for (long i = 0; i < degree; ++i) {
		c = p.rep[i] >> bits;
		truncate(c, logMod);
		res.rep[i] = c;
	}
	res.normalize();
}

void Ring2Utils::rightShift(CZZX& res, CZZX& p, const long& bits, const long& logMod, const long& degree) {
	rightShift(res.rx, p.rx, bits, logMod, degree);
	rightShift(res.ix, p.ix, bits, logMod, degree);
}

void Ring2Utils::rightShift(ZZX& res, ZZX& p, const long& bits, const long& degree) {
	ZZ c;
	res.SetLength(degree);
	for (long i = 0; i < degree; ++i) {
		res.rep[i] = p.rep[i] >> bits;
	}
	res.normalize();
}

void Ring2Utils::rightShift(CZZX& res, CZZX& p, const long& bits, const long& degree) {
	rightShift(res.rx, p.rx, bits, degree);
	rightShift(res.ix, p.ix, bits, degree);
}

void Ring2Utils::rightShiftAndEqual(ZZX& p, const long& bits, const long& logMod, const long& degree) {
	ZZ c;
	for (long i = 0; i < degree; ++i) {
		c = p.rep[i] >> bits;
		truncate(c, logMod);
		p.rep[i] = c;
	}
	p.normalize();
}

void Ring2Utils::rightShiftAndEqual(CZZX& p, const long& bits, const long& logMod, const long& degree) {
	rightShiftAndEqual(p.rx, bits, logMod, degree);
	rightShiftAndEqual(p.ix, bits, logMod, degree);
}

void Ring2Utils::rightShiftAndEqual(ZZX& p, const long& bits, const long& degree) {
	for (long i = 0; i < degree; ++i) {
		p.rep[i] >>= bits;
	}
	p.normalize();
}

void Ring2Utils::rightShiftAndEqual(CZZX& p, const long& bits, const long& degree) {
	rightShiftAndEqual(p.rx, bits, degree);
	rightShiftAndEqual(p.ix, bits, degree);
}

//-----------------------------------------

void Ring2Utils::inpower(ZZX& res, ZZX& p, const long& pow, const long& degree) {
	res.SetLength(degree);
	for (long i = 0; i < degree; ++i) {
		long ipow = i * pow;
		long shift = ipow % (2 * degree);
		res.rep[shift % degree] += shift < degree ? p.rep[i] : -p.rep[i];
	}
	res.normalize();
}

void Ring2Utils::inpowerAndEqual(ZZX& p, const long& pow, const long& degree) {
	ZZX tmp;
	inpower(tmp, p, pow, degree);
	p = tmp;
}

//-----------------------------------------

void Ring2Utils::truncate(ZZX& res, ZZX& p, const long& logMod, const long& degree) {
	res.SetLength(degree);
	res = p;
	for (long i = 0; i < degree; ++i) {
		truncate(res.rep[i], logMod);
	}
	res.normalize();
}

void Ring2Utils::truncate(CZZX& res,  CZZX& p, const long& logMod, const long& degree) {
	truncate(res.rx, p.rx, logMod, degree);
	truncate(res.ix, p.ix, logMod, degree);
}

void Ring2Utils::truncateAndEqual(ZZX& p, const long& logMod, const long& degree) {
	for (long i = 0; i < degree; ++i) {
		truncate(p.rep[i], logMod);
	}
	p.normalize();
}

void Ring2Utils::truncateAndEqual(CZZX& p, const long& logMod, const long& degree) {
	truncateAndEqual(p.rx, logMod, degree);
	truncateAndEqual(p.ix, logMod, degree);
}

void Ring2Utils::truncate(ZZ& c, const long& logMod) {
	c = sign(c) * trunc_ZZ(c, logMod);
}

void Ring2Utils::truncate(CZZ& c, const long& logMod) {
	truncate(c.r, logMod);
	truncate(c.i, logMod);
}


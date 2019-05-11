//---------------------------------------------------------
//! @file lambertW.h 
//! @brief ランベルトのW関数
//! f(w)=we^w　@n
//! ただし、e^w は指数関数、w は任意の複素数である。
//---------------------------------------------------------
#pragma once
#include <cmath>
#include <Core/greenTea2D.h>



class LambertW
{
private:
	static const double NAPIERS;
	static const double GSL_DBL_EPSILON;
	static const double c[];

	class gsl_sf_result
	{
	public:
		double val, err;
		gsl_sf_result() {
			val = err = 0;
		};
	};

	enum GSL_RETURN { GSL_SUCCESS, GSL_EMAXITER, GSL_EDOM };

	//!< ハレーの反復（式5.12、コーレスなど）
	static GSL_RETURN
		halley_iteration(
		double x,
		double w_initial,
		int max_iters,
		gsl_sf_result& result
		)
	{
			double w = w_initial;
			int i;

			for (i = 0; i<max_iters; i++) {
				double tol;
				const double e = exp(w);
				const double p = w + 1.0;
				double t = w*e - x;
				// prmcINTf("FOO: %20.16g  %20.16g\n", w, t);

				if (w > 0) {
					t = (t / p) / e;  // ニュートン反復
				}
				else {
					t /= e*p - 0.5*(p + 1.0)*t / p;  // ハレーの反復
				};

				w -= t;

				double mx = abs(w)>1.0 / (abs(p)*e) ? abs(w) : 1.0 / (abs(p)*e);

				tol = 10 * GSL_DBL_EPSILON * mx;

				if (abs(t) < tol)
				{
					result.val = w;
					result.err = 2.0*tol;
					return GSL_SUCCESS;
				}
			}

			// ここに来ることはない
			result.val = w;
			result.err = abs(w);
			return GSL_EMAXITER;
	}
	//!< そのシリーズは、ゼロに近いqのために表示される
	//  引数は、異なるブランチごとに異なる
	static double series_eval(double r)
	{
			const double t_8 = c[8] + r*(c[9] + r*(c[10] + r*c[11]));
			const double t_5 = c[5] + r*(c[6] + r*(c[7] + r*t_8));
			const double t_1 = c[1] + r*(c[2] + r*(c[3] + r*(c[4] + r*t_5)));
			return c[0] + r*t_1;
	}
	//=====================================================
	//!< エラーコードを持つ関数
	//=====================================================
	static GSL_RETURN gsl_sf_lambert_W0_e(double x, gsl_sf_result& result)
	{
		const double one_over_E = 1.0 / NAPIERS;
		const double q = x + one_over_E;

		if (x == 0.0) {
			result.val = 0.0;
			result.err = 0.0;
			return GSL_SUCCESS;
		}
		else if (q < 0.0) {
			// 厳密に言えば、これはエラーになります。
			// しかし、なぜならXとqを結ぶ演算の、私はいくつかのイプシロンのオーバーシュートの場合は少し緩いです。
			//次の答えは、そのような場合には非常に正確です。とにかく、我々はGSL_EDOMを返すことがあります。
			//
			result.val = -1.0;
			result.err = sqrt(-q);
			return GSL_EDOM;
		}
		else if (q == 0.0) {
			result.val = -1.0;
			result.err = GSL_DBL_EPSILON; // 0なのでえらーにできない, アクシデントによって、もしかしたら q == 0 
			return GSL_SUCCESS;
		}
		else if (q < 1.0e-03) {
			/* series near -1/E in sqrt(q) */
			const double r = sqrt(q);
			result.val = series_eval(r);
			result.err = 2.0 * GSL_DBL_EPSILON * abs(result.val);
			return GSL_SUCCESS;
		}
		else {
			const int MAX_ITERS = 10;
			double w;

			if (x < 1.0) {
				/* obtain initial approximation from series near x=0;
				* no need for extra care, since the Halley iteration
				* converges nicely on this branch
				*/
				const double p = sqrt(2.0 * NAPIERS * q);
				w = -1.0 + p*(1.0 + p*(-1.0 / 3.0 + p*11.0 / 72.0));
			}
			else {
				// 粗い漸近から初期近似を得る。
				w = log(x);
				if (x > 3.0) w -= log(w);
			}

			return halley_iteration(x, w, MAX_ITERS, result);
		}
	}


	static GSL_RETURN gsl_sf_lambert_Wm1_e(double x, gsl_sf_result& result)
	{
		if (x > 0.0) {
			return gsl_sf_lambert_W0_e(x, result);
		}
		else if (x == 0.0) {
			result.val = 0.0;
			result.err = 0.0;
			return GSL_SUCCESS;
		}
		else {
			const int MAX_ITERS = 32;
			const double one_over_E = 1.0 / NAPIERS;
			const double q = x + one_over_E;
			double w;

			if (q < 0.0) {
				// 上のW0ブランチのように、とにかくいくつかの合理的な答えを返す。
				result.val = -1.0;
				result.err = sqrt(-q);
				return GSL_EDOM;
			}

			if (x < -1.0e-6) {
				/* q = 0に関する系列から初期近似を得る
				* as long as we're not very close to x = 0.
				* 全シリーズを使用して、Qが小さすぎる場合に救済しようとすると、
				* ハリー反復が悪い収束特性を有し、非常に小さなQのための有限演算なので、
				* インクリメント交互およびpがゼロに近い。
				*/
				const double r = -sqrt(q);
				w = series_eval(r);
				if (q < 3.0e-3) {
					// この近似は十分です
					result.val = w;
					result.err = 5.0 * GSL_DBL_EPSILON * abs(w);
					return GSL_SUCCESS;
				}
			}
			else {
				// 漸近ゼロに近いから初期近似を得る。
				const double L_1 = log(-x);
				const double L_2 = log(-L_1);
				w = L_1 - L_2 + L_2 / L_1;
			}

			return halley_iteration(x, w, MAX_ITERS, result);
		}
	}
public:

	// 関数 w/ ナチュラルプロトタイプ

	static double W0(double x)
	{
		gsl_sf_result result;
		GSL_RETURN res = gsl_sf_lambert_W0_e(x, result);
		if (res == GSL_EMAXITER) {
			throw _T("反復が多すぎ");
		}
		return result.val;
	}

	static double W0(double x, bool *pIsErr)
	{
		gsl_sf_result result;
		GSL_RETURN res = gsl_sf_lambert_W0_e(x, result);
		if (res == GSL_EMAXITER) {
			*pIsErr = true;
		}
		return result.val;
	}

	static double W1(double x)
	{
		gsl_sf_result result;
		GSL_RETURN res = gsl_sf_lambert_Wm1_e(x, result);
		if (res == GSL_EMAXITER) {
			throw _T("反復が多すぎ");
		}
		return result.val;
	}
	static double W1(double x, bool *pIsErr)
	{
		gsl_sf_result result;
		GSL_RETURN res = gsl_sf_lambert_Wm1_e(x, result);
		if (res == GSL_EMAXITER) {
			*pIsErr = true;
		}
		return result.val;
	}

};
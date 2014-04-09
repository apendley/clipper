//go@ bash build-mingw32.sh
//Clipper C wrapper by Cosmin Apreutesei (public domain)
//Further modifications by Aaron Pendley
#include <stdint.h>
#include "clipper.cpp"

using namespace ClipperLib;

#ifdef __MINGW32__
#define export extern "C" __declspec (dllexport)
#else
#define export extern "C"
#endif

// clipper_polygon class

export Path* clipper_polygon_create(int n) {
	try {
		return new Path(n);
	} catch(...) {
		return 0;
	}
}

export void clipper_polygon_free(Path* poly) {
	delete poly;
}

export int clipper_polygon_size(Path* poly) {
	return poly->size();
}

export IntPoint* clipper_polygon_get(Path* poly, int i) {
	return &((*poly)[i]);
}

export double clipper_polygon_get_real_x(Path* poly, int i) {
	return ((*poly)[i]).X;
}

export double clipper_polygon_get_real_y(Path* poly, int i) {
	return ((*poly)[i]).Y;
}

export int clipper_polygon_add(Path* poly, int64_t x, int64_t y) {
	try {
		poly->push_back(IntPoint(x, y));
		return 0;
	} catch(...) {
		return 1;
	}
}

export Paths* clipper_polygon_simplify(Path* poly, PolyFillType fill_type) {
	try {
		Paths* out = new Paths();
		SimplifyPolygon(*poly, *out, PolyFillType(fill_type));
		return out;
	} catch(...) {
		return 0;
	}
}

export Path* clipper_polygon_clean(Path* poly, double distance) {
	try {
		Path* out = new Path();
		CleanPolygon(*poly, *out, distance);
		return out;
	} catch(...) {
		return 0;
	}
}

export void clipper_polygon_reverse(Path* poly) {
	ReversePath(*poly);
}

export int clipper_polygon_orientation(Path* poly) {
	return Orientation(*poly);
}

export double clipper_polygon_area(Path* poly) {
	return Area(*poly);
}

// clipper_polygons class

export Paths* clipper_polygons_create(int n) {
	try {
		return new Paths(n);
	} catch(...) {
		return 0;
	}
}

export void clipper_polygons_free(Paths* poly) {
	delete poly;
}

export int clipper_polygons_size(Paths* poly) {
	return poly->size();
}

export Path* clipper_polygons_get(Paths* poly, int i) {
	return &((*poly)[i]);
}

export void clipper_polygons_set(Paths* poly, int i, Path* e) {
	(*poly)[i] = *e;
}

export int clipper_polygons_add(Paths* poly, Path* e) {
	try {
		poly->push_back(*e);
		return 0;
	} catch(...) {
		return 1;
	}
}

export Paths* clipper_polygons_simplify(Paths* poly, PolyFillType fill_type) {
	try {
		Paths* out = new Paths();
		SimplifyPolygons(*poly, *out, PolyFillType(fill_type));
		return out;
	} catch(...) {
		return 0;
	}
}

export Paths* clipper_polygons_clean(Paths* poly, double distance) {
	try {
		Paths* out = new Paths(poly->size());
		CleanPolygons(*poly, *out, distance);
		return out;
	} catch(...) {
		return 0;
	}
}

export void clipper_polygons_reverse(Paths* poly) {
	ReversePaths(*poly);
}

export Paths* clipper_polygons_offset(Paths* poly, double delta, JoinType jointype, EndType_ endtype, double miter_limit) {
	try {
		Paths* out = new Paths();
		OffsetPaths(*poly, *out, delta, JoinType(jointype), EndType_(endtype), miter_limit);
		return out;
	} catch(...) {
		return 0;
	}
}

// clipper class

export double clipper_toreal(int64_t n) {
	return (double)n;
}

export Clipper* clipper_create() {
	try {
		return new Clipper();
	} catch(...) {
		return 0;
	}
}

export void clipper_free(Clipper* clipper) {
	delete clipper;
}

export int clipper_add_polygon(Clipper* clipper, Path* poly, PolyType poly_type, bool closed) {
	clipper->AddPath(*poly, PolyType(poly_type), closed);
}

export int clipper_add_polygons(Clipper* clipper, Paths* poly, PolyType poly_type, bool closed) {
	clipper->AddPaths(*poly, PolyType(poly_type), closed);
}

export void clipper_get_bounds(Clipper* clipper, IntRect* out) {
	*out = clipper->GetBounds();
}

export Paths* clipper_execute(Clipper* clipper, ClipType clipType,
									PolyFillType subjFillType,
									PolyFillType clipFillType) {
	try {
		Paths* solution = new Paths();
		clipper->Execute(ClipType(clipType), *solution,
											PolyFillType(subjFillType),
											PolyFillType(clipFillType));
		return solution;
	} catch(...) {
		return 0;
	}
}

export void clipper_clear(Clipper* clipper) {
	clipper->Clear();
}

export int clipper_get_reverse_solution(Clipper* clipper) {
	return clipper->ReverseSolution();
}

export void clipper_set_reverse_solution(Clipper* clipper, int reverse) {
	clipper->ReverseSolution(reverse);
}


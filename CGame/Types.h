#ifndef TYPES_H
#define TYPES_H

#include <cstdint>
#include <fstream>
#include <windows.h>

#define VALIDATE_SIZE( struc, size ) static_assert( sizeof( struc ) == size, "Invalid structure size of " #struc )

typedef class RwV3D	   CVector;
typedef class RwV3D	   CVector3D;
typedef class RwV3D	   VECTOR;
typedef class RwV2D	   CVector2D;
typedef const unsigned CU;
struct RwFrame;

struct Quaternion;

class RwV3D {
public:
	union {
		struct {
			float fX, fY, fZ;
		};
		float f[3];
	};

	RwV3D( float X = 0.0f, float Y = 0.0f, float Z = 0.0f );
	RwV3D( const RwV2D &v2d, float Z = 1.0f );

	/**
	 * @brief Очистка вектора
	 */
	void clear();
	/**
	 * @brief Проверка чист ли вектор
	 * @return возвращает @b true если каждый элемент вектора равен 0.0f
	 */
	bool isClear();
	/**
	 * @brief Нормализация вектора
	 * @details Приведение всех направлений вектора (fX, fY, fZ) к диапазону от -1.0 до +1.0
	 */
	void normalize();

	bool isNormalized();

	/**
	 * @brief Находит длину вектора
	 * @return Длина вектора
	 */
	float length();
	/**
	 * @brief Находит угол вектора по X и Y
	 * @return Угол Z
	 */
	float angle();
	/**
	 * @brief Находит угол между текущим вектором и входными координатами
	 * @param X координата X
	 * @param Y координата Y
	 * @return Угол Z
	 */
	float angle( const float &X, const float &Y );
	/**
	 * @brief Нахудит угол между двумя векторами по координатам X и Y
	 * @param r вектор
	 * @return Угол Z
	 */
	float angle( const RwV3D &r );

	/**
	 * @brief Алгебраическое точечное произведение двух векторов
	 * @param param вектор
	 * @return точечное произведение
	 */
	float DotProduct( const CVector *param ) const;
	/**
	 * @brief Скалярное произведение двух векторов
	 * @details Позволяет имея 2 вектора (например направление X и Z), найти направление третьего вектора (в
	 * нашем примере Z)
	 * @param param вектор
	 */
	void CrossProduct( const CVector *param );


	RwV3D operator+( const RwV3D &vecRight ) const {
		return RwV3D( fX + vecRight.fX, fY + vecRight.fY, fZ + vecRight.fZ );
	}
	RwV3D operator-( const RwV3D &vecRight ) const {
		return RwV3D( fX - vecRight.fX, fY - vecRight.fY, fZ - vecRight.fZ );
	}
	RwV3D operator*( const RwV3D &vecRight ) const {
		return RwV3D( fX * vecRight.fX, fY * vecRight.fY, fZ * vecRight.fZ );
	}
	RwV3D operator*( float fRight ) const { return RwV3D( fX * fRight, fY * fRight, fZ * fRight ); }
	RwV3D operator/( const RwV3D &vecRight ) const {
		return RwV3D( fX / vecRight.fX, fY / vecRight.fY, fZ / vecRight.fZ );
	}
	RwV3D operator/( float fRight ) const { return RwV3D( fX / fRight, fY / fRight, fZ / fRight ); }
	RwV3D operator-() const { return RwV3D( -fX, -fY, -fZ ); }

	void operator+=( float fRight ) {
		fX += fRight;
		fY += fRight;
		fZ += fRight;
	}
	void operator+=( const RwV3D &vecRight ) {
		fX += vecRight.fX;
		fY += vecRight.fY;
		fZ += vecRight.fZ;
	}
	void operator-=( float fRight ) {
		fX -= fRight;
		fY -= fRight;
		fZ -= fRight;
	}
	void operator-=( const RwV3D &vecRight ) {
		fX -= vecRight.fX;
		fY -= vecRight.fY;
		fZ -= vecRight.fZ;
	}
	void operator*=( float fRight ) {
		fX *= fRight;
		fY *= fRight;
		fZ *= fRight;
	}
	void operator*=( const RwV3D &vecRight ) {
		fX *= vecRight.fX;
		fY *= vecRight.fY;
		fZ *= vecRight.fZ;
	}
	void operator/=( float fRight ) {
		fX /= fRight;
		fY /= fRight;
		fZ /= fRight;
	}
	void operator/=( const RwV3D &vecRight ) {
		fX /= vecRight.fX;
		fY /= vecRight.fY;
		fZ /= vecRight.fZ;
	}

	bool operator==( const RwV3D &param ) const { return ( fX == param.fX && fY == param.fY && fZ == param.fZ ); }
	bool operator!=( const RwV3D &param ) const { return !operator==( param ); }

	bool operator==( float param[3] ) const { return ( fX == param[0] && fY == param[1] && fZ == param[2] ); }
	bool operator!=( float param[3] ) const { return !operator==( param ); }

	float squaredLength() const { return fX * fX + fY * fY + fZ * fZ; }

	bool operator<( const float &right ) const { return squaredLength() < right * right; }
	bool operator>( const float &right ) const { return squaredLength() > right * right; }
	bool operator<=( const float &right ) const { return !operator>( right ); }
	bool operator>=( const float &right ) const { return !operator<( right ); }

	bool operator<( const RwV3D &right ) const { return squaredLength() < right.squaredLength(); }
	bool operator>( const RwV3D &right ) const { return squaredLength() > right.squaredLength(); }
	bool operator<=( const RwV3D &right ) const { return !operator>( right ); }
	bool operator>=( const RwV3D &right ) const { return !operator<( right ); }

	bool operator<( float right[3] ) const {
		return squaredLength() < ( right[0] * right[0] + right[1] * right[1] + right[2] * right[2] );
	}
	bool operator>( float right[3] ) const {
		return squaredLength() > ( right[0] * right[0] + right[1] * right[1] + right[2] * right[2] );
	}
	bool operator<=( float right[3] ) const { return !operator>( right ); }
	bool operator>=( float right[3] ) const { return !operator<( right ); }
};

std::ostream &operator<<( std::ostream &out, const RwV3D &vec );

class RwMatrix {
public:
	RwV3D right;
	DWORD flags;
	RwV3D up;
	float pad_u;
	RwV3D at; // front
	float pad_a;
	RwV3D pos;
	float pad_p;

	RwMatrix();
	RwMatrix( const RwMatrix & );
	RwMatrix( Quaternion q );

	/**
	 * @brief Поворот матрицы в соответствии с кватернионом
	 * @param quater Кватернион
	 */
	void setQuaternion( const Quaternion &quater );
	/**
	 * @brief Возвращает повороты матрицы в виде кватерниона
	 * @return Кватернион
	 */
	Quaternion quaternion();
	/**
	 * @brief Инвертация матрицы
	 * @details Умножение на -1
	 */
	void invert();
	/**
	 * @brief Вращение матрицы
	 * @param param Вектор задающий вращение
	 * @param theta Угол вращения
	 * @return Повернутая матрица
	 */
	RwMatrix rotate( const RwV3D *param, const float &theta );

	RwMatrix rotX( const float &angle );
	RwMatrix rotY( const float &angle );
	RwMatrix rotZ( const float &angle );

	/**
	 * @brief Получает смещение относительно текущего объекта
	 * @details Координаты в векторе смещения: слева/справа, спереди/сзади, сверху/снизу
	 * @param offset вектор смещения
	 * @return смещенние относительно текущей позиции
	 */
	RwV3D getOffset( RwV3D offset );

	float getAngleZ();

	RwMatrix operator+( const RwMatrix &other ) const {
		RwMatrix matResult;
		matResult.right = right + other.right;
		matResult.at	= at + other.at;
		matResult.up	= up + other.up;
		matResult.pos	= pos + other.pos;
		return matResult;
	}
	RwMatrix operator-( const RwMatrix &other ) const {
		RwMatrix matResult;
		matResult.right = right - other.right;
		matResult.at	= at - other.at;
		matResult.up	= up - other.up;
		matResult.pos	= pos - other.pos;
		return matResult;
	}
	RwMatrix operator*( const RwMatrix &other ) const {
		RwMatrix matResult;
		matResult.right = ( *this ) * other.right;
		matResult.at	= ( *this ) * other.at;
		matResult.up	= ( *this ) * other.up;
		matResult.pos	= ( *this ) * other.pos;
		return matResult;
	}
	RwMatrix operator/( RwMatrix other ) const {
		other.invert();
		return ( *this ) * other;
	}
	RwV3D operator*( const RwV3D &vec ) const {
		return CVector( right.fX * vec.fX + at.fX * vec.fY + up.fX * vec.fZ,
						right.fY * vec.fX + at.fY * vec.fY + up.fY * vec.fZ,
						right.fZ * vec.fX + at.fZ * vec.fY + up.fZ * vec.fZ );
	}

private:
	void QuaternionToMatrix( const Quaternion &quater );
};

std::ostream &operator<<( std::ostream &out, const RwMatrix &mat );

class CMatrix : public RwMatrix {
	class RwMatrix *rwMatrix;
	int				haveRwMatrix;

public:
	void SyncRwMatrix();
	void UpdateRwMatrix();
};

/**
 * @brief Сжатый вектор
 * @details Каждый элемент вектора занимает 2 байта
 */
struct CompressedVector {
	WORD wX, wY, wZ;
};

/**
 * @brief Кватернион
 * @details Несет в себе информацию о вращение объекта. Эта информация хранится более компактно, чем в
 * матрице, однако для вращения требуется больше математических операций
 */
struct Quaternion {
	float fW, fX, fY, fZ;
};

struct RtQuat {
	RwV3D image;
	float real;
};

struct Detachable {
	RwV3D	position;
	uint8_t __unknown_12[4];
	RwV3D	vector;
	uint8_t __unknown_28[16];
};

struct CRect {
	float l;
	float t;
	float r;
	float b;
};
struct RwVRect {
	float x1;
	float y1;
	float x2;
	float y2;

	bool operator==( const RwVRect &r ) { return x1 == r.x1 && x2 == r.x2 && y1 == r.y1 && y2 == r.y2; }
	bool operator!=( const RwVRect &r ) { return !operator==( r ); }
};

#pragma pack( push, 1 )
class RwV2D {
public:
	float fX, fY;
	RwV2D( float X = 0.0f, float Y = 0.0f );
	RwV2D( const RwV3D &vec3d );

	/**
	 * @brief Очистка вектора
	 */
	void clear();
	/**
	 * @brief Проверка чист ли вектор
	 * @return возвращает @b true если каждый элемент вектора равен 0.0f
	 */
	bool isClear() const;
	/**
	 * @brief Нормализация вектора
	 * @details Приведение всех направлений вектора (fX, fY) к диапазону от -1.0 до +1.0
	 */
	void normalize();
	/**
	 * @brief Нормализация вектора к квадрату
	 * @details Приведение всех направлений вектора (fX, fY) к диапазону от -1.0 до +1.0
	 */
	void normalizeRect();

	/**
	 * @brief Находит длину вектора
	 * @return Длина вектора
	 */
	float length() const;

	/**
	 * @brief Алгебраическое точечное произведение двух векторов
	 * @param param вектор
	 * @return точечное произведение
	 */
	float DotProduct( const CVector *param ) const;
	/**
	 * @brief Скалярное произведение двух векторов
	 * @details Позволяет имея 2 вектора (например направление X и Z), найти направление третьего вектора (в
	 * нашем примере Z)
	 * @param param вектор
	 */
	void CrossProduct( const CVector *param );

	RwV2D operator+( const RwV2D &vecRight ) const { return RwV2D( fX + vecRight.fX, fY + vecRight.fY ); }
	RwV2D operator-( const RwV2D &vecRight ) const { return RwV2D( fX - vecRight.fX, fY - vecRight.fY ); }
	RwV2D operator*( const RwV2D &vecRight ) const { return RwV2D( fX * vecRight.fX, fY * vecRight.fY ); }
	RwV2D operator*( float fRight ) const { return RwV2D( fX * fRight, fY * fRight ); }
	RwV2D operator/( const RwV2D &vecRight ) const { return RwV2D( fX / vecRight.fX, fY / vecRight.fY ); }
	RwV2D operator/( float fRight ) const { return RwV2D( fX / fRight, fY / fRight ); }
	RwV2D operator-() const { return RwV2D( -fX, -fY ); }

	void operator+=( float fRight ) {
		fX += fRight;
		fY += fRight;
	}
	void operator+=( const RwV2D &vecRight ) {
		fX += vecRight.fX;
		fY += vecRight.fY;
	}
	void operator-=( float fRight ) {
		fX -= fRight;
		fY -= fRight;
	}
	void operator-=( const RwV2D &vecRight ) {
		fX -= vecRight.fX;
		fY -= vecRight.fY;
	}
	void operator*=( float fRight ) {
		fX *= fRight;
		fY *= fRight;
	}
	void operator*=( const RwV2D &vecRight ) {
		fX *= vecRight.fX;
		fY *= vecRight.fY;
	}
	void operator/=( float fRight ) {
		fX /= fRight;
		fY /= fRight;
	}
	void operator/=( const RwV2D &vecRight ) {
		fX /= vecRight.fX;
		fY /= vecRight.fY;
	}

	bool operator==( const RwV2D &param ) const { return ( fX == param.fX && fY == param.fY ); }
	bool operator!=( const RwV2D &param ) const { return !operator==( param ); }

	float squaredLength() const { return fX * fX + fY * fY; }

	bool operator<( const float &right ) const { return squaredLength() < right * right; }
	bool operator>( const float &right ) const { return squaredLength() > right * right; }
	bool operator<=( const float &right ) const { return !operator>( right ); }
	bool operator>=( const float &right ) const { return !operator<( right ); }

	bool operator<( const RwV2D &right ) const { return squaredLength() < right.squaredLength(); }
	bool operator>( const RwV2D &right ) const { return squaredLength() > right.squaredLength(); }
	bool operator<=( const RwV2D &right ) const { return !operator>( right ); }
	bool operator>=( const RwV2D &right ) const { return !operator<( right ); }
};

struct PsGlobalType {
	DWORD window;
	DWORD instance;
	int	  fullscreen;
	DWORD lastMousePos_X;
	DWORD lastMousePos_Y;
	DWORD __unknown_h14;
	DWORD diInterface;
	DWORD diMouse;
	DWORD diDevice1;
	DWORD diDevice2;
};

/**
 * @brief Структура глоабальных объектов RwEngine
 * @details В этой структуре хранятся базовые данные окна и указатели на обработчики
 */
struct RsGlobalType {
	char *				 appName;
	uint32_t			 maxWidth;
	uint32_t			 maxHeight;
	uint32_t			 frameLimit;
	uint32_t			 quit;
	struct PsGlobalType *ps;
	uint32_t			 keyboard;
	uint32_t			 mouse;
	uint32_t			 pad;
};

struct RwBBox {
	RwV3D sup;
	RwV3D inf;
};

struct RwObject {
	char	 type;
	char	 subType;
	char	 flags;
	char	 privateFlags;
	RwFrame *parent;
};

struct RwLLLink {
	RwFrame *next;
	int		 prev;
};

struct RwLinkList {
	RwLLLink link;
};

struct RwFrame {
	RwObject   object;
	RwLLLink   inDirtyListLink;
	RwMatrix   modelling;
	RwMatrix   ltm;
	RwLinkList objectList;
	RwFrame *  child;
	RwFrame *  next;
	int		   root;
};

struct RwObjectHasFrame {
	RwObject object;
	RwLLLink lFrame;
	int		 sync;
};

struct RwPlane {
	RwV3D normal;
	int	  distance;
};

struct RwFrustumPlane {
	RwPlane plane;
	char	closestX;
	char	closestY;
	char	closestZ;
	char	pad;
};

struct RwCamera {
	RwObjectHasFrame object;
	int				 projectionType;
	int				 beginUpdate;
	int				 endUpdate;
	RwMatrix		 viewMatrix;
	class RwRaster * frameBuffer;
	int				 zBuffer;
	RwV2D			 viewWindow;
	RwV2D			 recipViewWindow;
	RwV2D			 viewOffset;
	int				 nearPlane;
	float			 farPlane;
	int				 fogPlane;
	int				 zScale;
	int				 zShift;
	RwFrustumPlane	 frustrumPlanes[6];
	RwBBox			 frustrumBoundBox;
	RwV3D			 frustrumCorners[8];

	static RwCamera *get();
};
#pragma pack( pop )

#pragma pack( push, 8 )
struct CQueuedMode {
	__int16 Mode;
	float	Duration;
	__int16 MinZoom;
	__int16 MaxZoom;
};
struct ListItem_c {
	struct FxSystemBP_c *pPrev;
	struct FxSystemBP_c *pNext;
};
struct FxSystemBP_c {
	ListItem_c m_list;
	int		   nHash;
	int		   field_C;
	int		   field_10;
	int		   field_14;
	int		   field_18;
	int		   field_1C;
	int		   field_20;
};
struct List_c {
	struct FxSystemBP_c *pPrev;
	struct ListItem_c *	 pNext;
	int					 nCount;
};
#pragma pack( pop )

enum class RwPrimitiveType : int {
	NAPRIMTYPE,
	LINELIST,
	LINESTRIP,
	TRIANGLELIST,
	TRIANGLESTRIP,
	TRIANGLEFAN,
	POINTLIST,
};


#pragma pack( push, 8 )
struct RwD3D9Vertex {
	float x;
	float y;
	float z;
	float rhw;
	int	  emissiveColor;
	float u;
	float v;

	static RwD3D9Vertex *maVerticies() { return (RwD3D9Vertex *)0xC80468; }
};
struct _rwD3D9RasterExt {
	class IDirect3DTexture9 *  texture;
	DWORD					   palette;
	char					   alpha;
	char					   cube_face;
	char					   automipmapgen_compressed;
	char					   lockedMipLevel;
	class IDirect3DSurface9 *  lockedSurface;
	INT						   Pitch;
	void *					   pBits;
	DWORD					   d3dFormat;
	class IDirect3DSwapChain9 *swapChain;
	HWND *					   window;

	static _rwD3D9RasterExt *offset() { return *(_rwD3D9RasterExt **)0xB4E9E0; }
};
struct RwRaster {
	int							 parent;
	int							 cpPixels;
	int							 palette;
	int							 width;
	int							 height;
	int							 depth;
	int							 stride;
	__int16						 nOffsetX;
	__int16						 nOffsetY;
	char						 cType;
	char						 cFlags;
	char						 privateFlags;
	char						 cFormat;
	int							 originalPixels;
	int							 originalWidth;
	int							 originalHeight;
	int							 oriiginalStride;
	class IDirect3DBaseTexture9 *data; // Этого нет, но есть магический оффсет, который сюда и указывает

	_rwD3D9RasterExt *rwD3D9RasterExt() {
		return (_rwD3D9RasterExt *)( DWORD( this ) + *(DWORD *)0xb4e9e0 );
		//return (_rwD3D9RasterExt *)( (char *)this + (DWORD)_rwD3D9RasterExt::offset() );
	}
};
struct RwTexture {
	RwRaster *raster;
	int		  dict;
	char	  gap8[8];
	char	  name[32];
	char	  mask[32];
	char	  filterAddressing;
	int		  refCount;
};
struct CTexture {
	RwTexture *texture = nullptr;
};

struct RwTexDictionary {
	char					dict[16];
	RwLLLink				lInInstance[2];
	static RwTexDictionary *vehicle() { return *(RwTexDictionary **)0xB4E688; }
};

struct CAnimBlendClumpData {
	void *					   m_pLastAssociationLink;
	struct RwFrame *		   frame;
	unsigned int			   m_nNumBones;
	int						   field_C;
	struct AnimBlendFrameData *m_pBones;
};
struct RpClump {
	RwObject object;

	/* Information about all the Atomics */
	RwLinkList atomicList;

	/* Lists of lights and cameras */
	RwLinkList lightList;
	RwLinkList cameraList;

	/* The clump in a world */
	RwLLLink inWorldLink;
	int( __cdecl *callback )( int );
};
struct RwRGBA {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t alpha;
	bool	operator==( const RwRGBA &r ) {
		   return red == r.red && green == r.green && blue == r.blue && alpha == r.alpha;
	}
	bool operator!=( const RwRGBA &r ) { return !operator==( r ); }
};
struct RwSurfaceProperties {
	float ambient;
	int	  specular;
	float diffuse;
};
struct RpMaterial {
	RwTexture *			texture;
	RwRGBA				color;
	int					pipeline;
	RwSurfaceProperties surfaceProps;
	__int16				refCount;
	__int16				pad;
};
struct RpMaterialList {
	RpMaterial **materials;
	int			 numMaterials;
	int			 space;
};
struct RpGeometry {
	RwObject	   object;
	int			   flags;
	__int16		   lockedSinceLastInst;
	__int16		   refCount;
	int			   numTriangles;
	int			   numVertices;
	int			   numMorphTargets;
	int			   numTexCoordSets;
	RpMaterialList matList;
	int			   triangles;
	int			   preLitLum;
	int			   texCoords[8];
	int			   mesh;
	int			   resEntry;
	int			   morphTarget;
};
struct RwSphere {
	RwV3D center;
	float radius;
};
struct RpInterpolator {
	int		flags;
	__int16 startMorphTarget;
	__int16 endMorphTarget;
	int		time;
	int		recipTime;
	int		position;
};
struct RxPipeline {
	int locked;
	int numNodes;
	int nodes;
	int packetNumClusterSlots;
	int embeddedPacketState;
	int embeddedPacket;
	int numInputRequirements;
	int inputRequirements;
	int superBlock;
	int superBlockSize;
	int entryPoint;
	int pluginId;
	int pluginData;
};
struct RwResEntry {
	RwLLLink	 link;						 /* Node in the list of resource elements */
	int			 size;						 /* Size of this node */
	void *		 owner;						 /* Owner of this node */
	RwResEntry **ownerRef;					 /* Pointer to pointer to this (enables de-alloc) */
	void ( *destroyNotify )( RwResEntry * ); /* This is called right before destruction */
};
struct RpAtomic {
	RwObjectHasFrame object;

	/* Information for an instance */
	struct RwResEntry *repEntry;

	/* Triangles making the object */
	RpGeometry *geometry;

	/* Interpolated bounding sphere (in object space and world space) */
	RwSphere boundingSphere;
	RwSphere worldBoundingSphere;

	/* Connections to other atomics */
	RpClump *clump;
	RwLLLink inClumpLink;

	/* callbacks */
	RpAtomic *( *renderCallBack )( RpAtomic * );

	/* Interpolation animation pointer */
	RpInterpolator interpolator;

	/* Counter for checks of "render has occurred already" */
	uint16_t renderFrame;
	uint16_t pad;

	/* Connections to sectors */
	RwLinkList llWorldSectorsInAtomic;

	/* The Atomic object pipeline for this Atomic */
	RxPipeline *pipeline;
};
struct tColLighting {
	__int8 _bf0;
};
struct CColPoint {
	CVector			m_vecPoint;
	float			field_C;
	CVector			m_vecNormal;
	float			field_1C;
	unsigned __int8 m_nSurfaceTypeA;
	unsigned __int8 m_nPieceTypeA;
	tColLighting	m_nLightingA;
	uint8_t			surfTypeId;
	unsigned __int8 m_nSurfaceTypeB;
	unsigned __int8 m_nPieceTypeB;
	tColLighting	m_nLightingB;
	char			_pad2;
	float			m_fDepth;
};
struct CRideAnimData {
	unsigned int m_nAnimGroup;
	float		 m_fSteerAngle;
	float		 m_fAnimLean;
	int			 dwordC;
	float		 dword10;
	float		 m_fHandlebarsAngle;
	float		 m_fAnimPercentageState;
};
struct CSprite2d {
	void *m_pTexture;
};
struct RwD3D9DisplayMode {
	UINT  Width;
	UINT  Height;
	UINT  RefreshRate;
	DWORD Format;
	int	  flags;

	static int &			  currentId();
	static RwD3D9DisplayMode *current();
	static RwD3D9DisplayMode *modes();
	static void				  apply( int mode );
};
struct CColData {
	int		field_0;
	__int16 field_4;
	char	m_nNoOfLines;
	char	field_7;
	int		field_8;
	int		field_C;
	void *	pSuspensionLines;
};
struct CColModel {
	RwBBox	  bbox;
	RwSphere  sphere;
	char	  field_28;
	char	  flags;
	char	  field_2A;
	char	  field_2B;
	CColData *m_pColData;
};
struct RwVideoMode {
	int width;
	int height;
	int depth;
	int flag;
	int refRate;
	int format;
};
#pragma pack( pop )


/**
 * @brief Перечисление моделий объектов
 * @details Модели разбиты на группы и отличаются префиксами
 * @list ped - модели людей
 * @list car - модели машин
 * @list spec - спец-модель
 * @list mini - маленькая модель, являющаяся аналогом большой модели
 * @list heli - модели вертолетов
 * @list boat - модели лодок
 * @list mtruck - модели грузовиков
 * @list bike - модели мотоциклов
 * @list bmx - модели велосипедов
 * @list train - модели поездов
 * @list trailer - модели трейлеров
 * @list quad - модель квадрацикла
 * @list universal - модель катера на воздушной падушке (по факту самолет с малой тягой)
 * @list weapon - модели оружия
 * @list fuck - модели, использование которых может привести к крашу
 */
enum eModelIndex {
	ped_cj	   = 0,
	ped_male01 = 7,

	car_landstal			 = 400,
	car_bravura				 = 401,
	car_buffalo				 = 402,
	car_linerun				 = 403,
	car_peren				 = 404,
	car_sentinel			 = 405,
	spec_car_firetruk		 = 407, //Пожарка с водой
	car_trash				 = 408,
	car_stretch				 = 409,
	car_manana				 = 410,
	car_infernus			 = 411,
	car_voodoo				 = 412,
	car_pony				 = 413,
	car_mule				 = 414,
	car_cheetah				 = 415,
	spec_car_ambulan		 = 416,
	car_moonbeam			 = 418,
	car_esperant			 = 419,
	car_taxi				 = 420,
	car_washing				 = 421,
	car_bobcat				 = 422,
	car_mrwhoop				 = 423,
	car_bfinject			 = 424,
	car_premier				 = 426,
	spec_car_enforcer		 = 427,
	car_securica			 = 428,
	car_banshee				 = 429,
	car_bus					 = 431,
	spec_army_car_rhino		 = 432,
	car_barracks			 = 433,
	car_hotknife			 = 434,
	car_previon				 = 436,
	car_coach				 = 437,
	car_cabbie				 = 438,
	car_stallion			 = 439,
	car_rumpo				 = 440,
	mini_car_rcbandit		 = 441,
	car_romero				 = 442,
	car_packer				 = 443,
	car_admiral				 = 445,
	car_turismo				 = 451,
	car_flatbed				 = 455,
	car_yankee				 = 456,
	car_caddy				 = 457,
	car_solair				 = 458,
	car_topfun				 = 459,
	car_glendale			 = 466,
	car_oceanic				 = 467,
	car_patriot				 = 470,
	car_hermes				 = 474,
	car_sabre				 = 475,
	car_zr350				 = 477,
	car_walton				 = 478,
	car_regina				 = 479,
	car_comet				 = 480,
	car_burrito				 = 482,
	car_camper				 = 483,
	car_baggage				 = 485,
	spec_car_dozer			 = 486,
	car_rancher				 = 489,
	spec_polici_car_fbiranch = 490,
	car_virgo				 = 491,
	car_greenwoo			 = 492,
	car_hotring				 = 494,
	car_sandking			 = 495,
	car_blistac				 = 496,
	car_boxville			 = 498,
	car_benson				 = 499,
	car_mesa				 = 500,
	car_hotrina				 = 502,
	car_hotrinb				 = 503,
	car_bloodra				 = 504,
	car_rnchlure			 = 505,
	car_supergt				 = 506,
	car_elegant				 = 507,
	car_journey				 = 508,
	car_petro				 = 514,
	car_rdtrain				 = 515,
	car_nebula				 = 516,
	car_majestic			 = 517,
	car_buccanee			 = 518,
	spec_car_cement			 = 524,
	spec_car_towtruck		 = 525,
	car_fortune				 = 526,
	car_cadrona				 = 527,
	spec_polici_car_fbitruck = 528,
	car_willard				 = 529,
	spec_car_forklift		 = 530,
	car_tractor				 = 531,
	spec_car_combine		 = 532,
	car_feltzer				 = 533,
	car_remingtn			 = 534,
	car_slamvan				 = 535,
	car_blade				 = 536,
	car_vincent				 = 540,
	car_bullet				 = 541,
	car_clover				 = 542,
	car_sadler				 = 543,
	car_firela				 = 544, //Пожарка
	car_hustler				 = 545,
	car_intruder			 = 546,
	car_primo				 = 547,
	car_cargobob			 = 548,
	car_tampa				 = 549,
	car_sunrise				 = 550,
	car_merit				 = 551,
	car_utility				 = 552,
	car_yosemite			 = 554,
	car_windsor				 = 555,
	car_uranus				 = 558,
	car_jester				 = 559,
	car_sultan				 = 560,
	car_stratum				 = 561,
	car_elegy				 = 562,
	mini_car_rctiger		 = 564, //Мини-танк
	car_flash				 = 565,
	car_tahoma				 = 566,
	car_savanna				 = 567,
	car_bandito				 = 568,
	spec_car_kart			 = 571,
	car_mower				 = 572, //Газонокосилка
	car_sweeper				 = 574,
	car_broadway			 = 575,
	car_tornado				 = 576,
	car_dft30				 = 578,
	car_huntley				 = 579,
	car_stafford			 = 580,
	car_newsvan				 = 582,
	car_tug					 = 583,
	car_emperor				 = 585,
	car_euros				 = 587,
	car_hotdog				 = 588,
	car_club				 = 589,
	mini_polici_car_rccam	 = 594, //Ведро
	spec_polici_car_copcarla = 596,
	spec_polici_car_copcarsf = 597,
	spec_polici_car_copcarvg = 598,
	spec_polici_car_copcarru = 599,
	car_picador				 = 600,
	car_swatvan				 = 601,
	car_alpha				 = 602, // use
	car_phoenix				 = 603,
	car_glenshit			 = 604,
	car_sadlshit			 = 605,
	car_boxburg				 = 609,

	mtruck_dumper	= 406,
	mtruck_monster	= 444,
	mtruck_monstera = 556,
	mtruck_monsterb = 557,
	mtruck_duneride = 573,

	bike_pizzaboy			 = 448,
	bike_pcj600				 = 461,
	bike_faggio				 = 462,
	bike_freeway			 = 463,
	bike_sanchez			 = 468,
	bike_fcr900				 = 521,
	bike_nrg500				 = 522,
	spec_polici_bike_copbike = 523,
	bike_bf400				 = 581,
	bike_wayfarer			 = 586,

	quad_quad = 471,

	bmx_bmx	   = 481,
	bmx_bike   = 509,
	bmx_mtbike = 510,

	heli_leviathn		   = 417,
	spec_army_heli_hunter  = 425,
	spec_army_heli_seaspar = 447,
	mini_heli_rcraider	   = 465,
	heli_sparrow		   = 469,
	heli_maverick		   = 487,
	heli_vcnmav			   = 488,
	fuck_heli_polmav	   = 497,
	mini_heli_rcgoblin	   = 501,
	heli_cargobob		   = 548,
	heli_raindanc		   = 563,

	plane_skimmer			= 460,
	mini_plane_rcbaron		= 464,
	spec_army_plane_rustler = 476,
	plane_beagle			= 511,
	spec_plane_cropdust		= 512,
	spec_plane_stunt		= 513,
	plane_shamal			= 519,
	spec_army_plane_hydra	= 520,
	plane_nevada			= 553,
	plane_at400				= 577,
	plane_androm			= 592,
	plane_dodo				= 593,

	universal_vortex = 539,

	spec_polici_boat_predator = 430,
	boat_squalo				  = 446,
	boat_speeder			  = 452,
	boat_reefer				  = 453,
	boat_tropic				  = 454,
	boat_coastg				  = 472,
	boat_dinghy				  = 473,
	boat_marquis			  = 484,
	boat_jetmax				  = 493,
	boat_launch				  = 595,

	train_tram	   = 449,
	train_freight  = 537,
	train_streak   = 538,
	train_freiflat = 569,
	train_streakc  = 570,
	train_freibox  = 590,

	trailer_artict1	 = 435,
	trailer_artict2	 = 450,
	trailer_petrotr	 = 584,
	trailer_artict3	 = 591,
	trailer_bagboxa	 = 606,
	trailer_bagboxb	 = 607,
	trailer_tugstair = 608,
	trailer_farmtr1	 = 610,
	trailer_utiltr1	 = 611,


	weapon_BrassKnuckles = 331,
	weapon_GolfClub		 = 333,
	weapon_Nitestick,
	weapon_Knife,
	weapon_BaseballBat,
	weapon_Shovel,
	weapon_PoolCue,
	weapon_Katana,
	weapon_Chainsaw = 341,
	weapon_Grenade,
	weapon_Teargas,
	weapon_MolotovCocktail,
	weapon_Pistol = 346,
	weapon_SilencedPistol,
	weapon_DesertEagle,
	weapon_Shotgun,
	weapon_SawnOffShotgun,
	weapon_SPAZ12,
	weapon_MicroUZI,
	weapon_MP5,
	weapon_AK47 = 355,
	weapon_M4,
	weapon_CountryRifle,
	weapon_SniperRifle,
	weapon_RocketLauncher,
	weapon_HeatSeekingRPG,
	weapon_FlameThrower,
	weapon_Minigun,
	weapon_RemoteExplosives,
	weapon_Detonator,
	weapon_SprayCan,
	weapon_FireExtinguisher,
	weapon_Camera,
	weapon_Dildo1 = 321,
	weapon_Dildo2,
	weapon_Vibe1,
	weapon_Vibe2,
	weapon_Flowers,
	weapon_Cane,
	weapon_NVGoggles = 368,
	weapon_IRGoggles,
	weapon_Parachute = 371,
	weapon_Tech9
};

#endif // TYPES_H

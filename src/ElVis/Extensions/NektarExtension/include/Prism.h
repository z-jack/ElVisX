#ifndef Prism_H
#define Prism_H

class Prism: public Element
{
	private:
	public:
		// Constructors
		Prism();            // default constructor
		Prism(Element *);   // constructor
		Prism(int i_d, char ty, int *qsize, int *jsize, Coord *X);
		Prism(int i_d, char ty, int L, int Qa, int Qb, int Qc, Coord *X);

		// Memory routines
		void Mem_J(int *list, char Prismp);
		void Mem_Q();

		void Mem_shift(double *, double *);			// updates storage pters
		void Mem_free();                           	// frees existing storage

		// Operators
		Prism& operator=(Prism&);	// assignement operator
		Prism& operator*=(Prism&);  // mulitplying operator
		Prism& operator*=(double&); // mulitplying operator
		Prism& operator+=(Prism&);  // addition operator

		// Local MaPrismx builders
		void MassMat (LocMat *);    // return mass-maPrism(ces)
		void MassMatC(LocMat *);
		void HelmMatC(LocMat *, Metric *lambda);	// return Helmholtz op.
		void LapMat  (LocMat *);                    // return Laplacian op.
		void Add_robin_matrix(LocMat *helm, Bndry *rbc, AdvVel *vel);
		void mat_free(LocMat *m);
		LocMat *mat_mem();
		void fill_diag_massmat();               // fill modes with mass diagonal
		void fill_diag_helmmat(Metric *lambda); // fill modes with helm diagonal

		// Transforms and inner-products
		void   Jbwd(Element*, Basis*);
		void   Jbwdfac1(int face, double *vj, double *v);
		void   Jfwd(Element*);
		double iprod(Mode *x, Mode *y);
		double iprodlap(Mode *x, Mode *y, Mode *fac);

		void HelmHoltz(Metric *lambda);
		void form_diprod(double *u1, double *u2, double *u3, Mode *m);

		// orthogonal transform routines
		void Obwd  (double *, double *, int);
		void Ofwd  (double *, double *, int);
		void Ofwd  (double *, double *, int, int);
		void Add_Surface_Contrib(Element *, double *in, char dir);
		void Add_Surface_Contrib(Element *, double *in, char dir, int edge);
		void Add_Surface_Contrib(Element *, double *in, char dir, int edge,
								 int invjac);
		void Add_Surface_Contrib(double *in, char dir, int edge);
		void Add_Surface_Contrib(double *in, char dir,  int edge, int invjac);
		void fill_edges(double *ux, double *uy, double *uz);

		void SubtractBC(double alpha, double  beta, int Bface,  Element *out);

		// Global maPrismx routines
		void condense(LocMat *m, Bsystem *Ubsys, char pack);
		void project(LocMat *m, Bsystem *Ubsys);
		void LowEnergyModes(Bsystem *B, int *Ne, int *Nf,
		                    double ***Rv, double ***Rvi, double ***Re);
		void MakeLowEnergyModes(Bsystem *B, int *Ne, int *Nf,
		                        double ***Rv, double ***Rvi, double ***Re);

		void Sign_Change();

		// Bndry routines
		Bndry *gen_bndry(char bc, int face, ...);
		Bndry *gen_bndry(AdvVel  *vel, char bc, int face, ...);
		void  update_bndry(Bndry *Ubc, int save);
		void   MemBndry(Bndry *B, int face, int Je);
		void JtransEdge(Bndry *B, int id, int loc, double *f);
		void JtransFace(Bndry *B, double *f);
		void MakeFlux(Bndry *B, double *f, AdvVel *vel = (AdvVel *) NULL);


		// Element Identifier
		Nek_Facet_Type identify()
		{
			return Nek_Prism;
		}         // identify

		// Transformation routines
		void Trans(Element *, Nek_Trans_Type);		// Transform to Prism
		void Iprod(Element *);                      // Inner product to Prism
		void Iprod_d (Element *,Basis *, Basis *);  // Inner product to Prism
		void Iprod_3d(Element *,Basis *, Basis *, Basis *);
													// Inner product to Prism

		// Derivatives routines
		void Grad (Element *, Element *, Element *, char Prismp);
		void Grad_d(double *, double *, double *, char Prismp);
		void Grad_h(double *, double *, double *, double *, char Prismp);
		void getD(double ***da, double ***dat,double ***db,double ***dbt,
		          double ***dc, double ***dct);
		// Get differential maPrismx

		void fillElmt(Mode *v);
		void fill_gradbase(Mode *gb, Mode *m, Mode *mb, Mode *fac);
		Basis *getbasis();
		Basis *derbasis();

		// Co-ordinate functions
		void set_curved(Curve*)
		{
			;
		}                         // fix curve sides
		void coord(Coord *X);                          // get quadrature coords
		void fillvec(Mode *v, double *f);                  //
		void straight_elmt(Coord *X);                      //
		void curved_elmt(Coord *X);                        //
		void straight_edge(Coord *X, int edge);            //
		void straight_face(Coord *X, int face,int trip);   //
		void GetFaceCoord(int face, Coord *X);             //

		// Error functions
		void Set_field(const char *sPrismng);			// set field to function
		void Error(const char *sPrismng);				// compare with function
		double L2_error_elmt(const char *sPrismng);
		double H1_error_elmt(const char *sPrismng);
		void Verror(double *u, const char *sPrismng);
		double Int_error(const char *sPrismng);
		double Norm_li();
		double Norm_l2();
		void Norm_l2m(double *l2, double *area);
		double Norm_h1();
		void Norm_h1m(double *h1, double  *area);

		// Curved sides
		void set_curved_elmt(Element_List*);
		void genArc(double *x, double *y);
		void genNaca4(double *x, double *y);
		void genFile(double *x, double *y);

		void CoordTransEdge(double *f, double *fhat, int edge);
		void get_mmat1d(double **mat, int L);

		// Geomec factors
		void set_geofac();
		void free_geofac();

		void Surface_geofac(Bndry *B);
		void InterpToFace1(int from_face, double *f, double *fi);
		void InterpToGaussFace(int from_face, double *f,
		                       int qaf, int qbf, double *fi);

		void set_solve(int fac, int mask);
		void Add_flux_terms(Bndry *Ebc);
		void setbcs(Bndry *Ubc, double *bc);
		void GetFace(double*, int, double *);

		void dump_mesh(FILE*);

		int  Nfmodes();
		int  vnum (int,int);
		int  fnum (int,int);
		int  fnum1(int,int);
		int  ednum (int,int);
		int  ednum1(int,int);
		int  ednum2(int,int);

		int dim()
		{
			return 3;
		}
		int Nfverts(int);

		void fill_column(double **Mat, int loc, Bsystem *B, int nm, int offset);
		void WeakDiff(Mode *m, double *ux, double *uy,double *uz, int con);

		int  data_len(int *size);
		void  Copy_field(double *, int *);

		void close_split(Element_List *EL,Bndry **Ubc,int nfields,int *&flag);
		void split_element(Element_List *EL,Bndry **Ubc,int nfields,int *&flag);
		void split_edge(int edg, Element_List *EL, Bndry **Ubc, int nfields);

		void delete_element(Element_List *EL);

		void set_edge_geofac();
		void set_edge_geofac(int invjac);
		void PutFace(double*, int);

		void GetZW(double **za, double **wa, double **zb, double **wb,
				   double **zc, double **wc);

		int edvnum(int,int);

		// Particle.C routines
		int        intersect_bnd    (Coord *Xi, double *vp,
		                             double *dt_remain, int *face);
		int        lcoords2face    (Coord *Xi, int *fac);
		void       face2lcoords    (Coord *Xi, int *fac);
		void       Cart_to_coll    (Coord csi, Coord *A);
		void       Coll_to_cart    (Coord A, Coord *csi);

		// local identifiers
		int get_face_q1(int faceid)
		{
			switch(faceid)
			{
				case 0:
					return qa;
				case 1:
					return qa;
				case 2:
					return qb;
				case 3:
					return qa;
				case 4:
					return qb;
				default:
					fprintf(stderr,"Prism:get_face_q1: Unknown faceid");
					exit(1);
			}
		}

		int get_face_q2(int faceid)
		{
			switch(faceid)
			{
				case 0:
					return qb;
				case 1:
					return qc;
				case 2:
					return qc;
				case 3:
					return qc;
				case 4:
					return qc;
				default:
					fprintf(stderr,"Prism:get_face_q2: Unknown faceid");
					exit(1);
			}
		}
};

#endif





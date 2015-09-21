c %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
c
c mestayer - Jan. 14, 2008 - 
c update - Feb. 6 - extend the outputs to include
c parameters of the endplates and top and bottom plates of
c the chambers as well as the gas-bag planes
c update - Feb. 27 - making subroutines for common tasks
c like finding the intersection of a line and a plane
c update - Mar. 4 - extending calculations to include the
c parameters of the "mother volume" which is essentially
c the shape of one region's dc "box"
c update - June 18 - cleaning up things due to my switch from
c  6 layers (sense only) to 8 layer (guards and sense)
c update - July 21 - adding explanation about generalized trapezoid
c  layer volumes
c update - September 3, 2008 - add "mini-stagger"
c
c update - June 10, 2010 - print out info for ALL 22 layers, incl. fields
c update - Jul 21, 2010 - added comments to explain 'tweaking' of geometry
c  to agree with designer Cyril Wiggin's numbers from his cad file
c update - May 24, 2011 - I have now 'tweaked' the region 1 geometry
c to agree with Cyril's numbers
c update - July 14, 2015 - I have again 'tweaked' the numbers to agree with the
c  new ideal positions

      program dcgeom12

c     Lay out the drift chamber geometry for CLAS12
c     companion document is dc_geometry12.latex

c     units are cm, deg, coordinate system is the "internal
c     dc coordinate system", as defined in dc_geometry12.latex,
c     cartesian coord. system: z along beam axis, x outward in
c     sector mid-plane
c
      implicit none
c
c  the essential 7 parameters (with 6 values each for the 6 s.l.'s)
c  (definitions and explanations given below) 
c
      real ministagger(6)
      real dist2tgt(6),thopen(6),thtilt(6),thster(6),thmin(6)
      real dlayer(6),xoffset(6),r
      real frontgap(3),midgap(3),backgap(3)
      real rfront(3),rback(3),regthickness(3)
c  indices to wires, planes, superlayers, layers
      integer i,iwir,iplane,ireg,isup,ilayer,isup1,isup2,ifirst
c  guard wire "marked" in a superlayer, corresponding to thmin
      integer ifirstwir(6),isenselayer,isensewir 
      real sup,layer,wir
c  direction cosines of wire plane normals and wire directions
      real cplane(3),cwire(3)
c  a test parameter, equals zero if a certain point is in a certain plane
      real plane
c  dir. cosines of normals to rh and lh endplates
      real crhplate(3),clhplate(3)
      real xplates(3)
      real r1dist,x0mid,y0mid,z0mid,x1mid,y1mid,z1mid
      real numxr,numyr,numzr,numxl,numyl,numzl
      real denomxr,denomyr,denomzr,denomxl,denomyl,denomzl
      real dist1mid,dw,dw2
      real xmid(3,114),angmid(114)
      real xcenter(3,114),wirespan(6,22)
      real lyrangle(6,22),angle
      real xpoint1(3),xpoint2(3),xpoint3(3),wir2wir
      real xmidwire(3)
      real xright(3,114)
      real xleft(3,114)
      real xrightwire(3),xleftwire(3)
      real wirelenr,wirelenl
      real wirelength(114),layerthickness(6),lyrthick
      real wireleneng
      real degrad,pi
      real c,s,x,y,z,xrtpl,yrtpl,zrtpl,xlfpl,ylfpl,zlfpl
      real delx1,delx2,dely,xx1,xx2,xz1,xz2
      real delx1lyr(6,22),delx2lyr(6,22),delylyr(6,22)
      real center_m(3,3),dx,dy,dz
      real xlyr(3,6,22),delxlyr(3,6,22)
      real ctilt,stilt,cster,sster
      real sum1,sum2
      real test(8)
      data test/5.87663,66.03787,6.56789,66.80991,5.87664,68.936,
     $     6.68479,69.74416/
      integer itest
      real diff
c

c--------------------------------------------------------------------------c
c Here is where we load in the values of the essential geometry parameters
c--------------------------------------------------------------------------c
c   ministagger is the distance that the sense wire is moved to the "right" or to
c   the "left" relative to its symmetric position wrt the six surrounding field wires
c   Note: sense wires in layers 1,3,5 are moved away from beam line, 2,4,6 toward beam line
      data ministagger/4*0.,0.030,0.030/
c   dist2tgt is the distance from the target to the first guard wire plane in each superlayer
c  new values as of 7/14/2015
      data dist2tgt/228.078,238.687,351.544,371.773,489.099,511.236/
c   frontgap is the distance between the upstream gas bag and the
c   first guard wire layer (assuming a flat gas bag!) - for each region
      data frontgap/2.5,2.5,2.5/
c   midgap is the distance between the last guard wire layer of one superlayer
c  and the first guard wire layer of the next superlayer - for each region
      data midgap/2.5,7.161,2.5/
c   backgap is the distance between the last guard wire layer of a region and
c   the downstream gas bag - for each region
      data backgap/2.5,2.5,2.5/
c   thopen is the opening angle between endplate planes in each superlayer
      data thopen/2*59.,2*60.,2*59/
c   thtilt is the tilt angle (relative to z) of the six superlayers
      data thtilt/6*25./
c   thster is the stereo angle of the wires in the six superlayers
c   note: thster is the angle of rotation about the normal to the wire plane
      data thster/-6.,6.,-6.,6.,-6.,6./
c   thmin is the polar angle to the first guard wire's "mid-point" where the
c   wire mid-point is the intersection of the wire with the chamber mid-plane
c   I 'tweaked' the thmin for reg.1 to agree with Cyril's numbers
      data thmin/4.694,4.495,4.812,4.771,4.333,4.333/
c   dlayer is the distance between wire planes
      data dlayer/0.3861,0.4042,0.6219,0.6586,0.9351,0.9780/
c   xoffset is the distance between the line of intersection of the two endplate
c   planes and the beam line (NOTE: this intersection line is parallel to the beamline)
      data xoffset/2*8.298,2*20.296,2*18.054/
c   first "marked" wire in a guard layer; corresponding to thmin; because wires
c    can be too short or too close to the nose plate, this is the first wire
c    actually strung; i.e. if ifirstwir=2, it means that the layer starts from
c    wire 2, and not from wire 1
      data ifirstwir/6*1/
c
      data degrad/57.2957795/
      data ifirst/0./
c-------------------------------------------------------------------------
c NOW, CALCULATE THE OUTER CHAMBER BOUNDARIES
c
c     calculate the distance from the target to the first guard wire plane of the 
c     second superlayer in each chamber from the gap values
c
      do ireg=1,3
         isup1=2*ireg-1
         isup2=isup1+1
         dist2tgt(isup2)=dist2tgt(isup1)+21.*dlayer(isup1)+
     $        +midgap(ireg)
         layerthickness(isup1)=3.*dlayer(isup1)
         layerthickness(isup2)=3.*dlayer(isup2)
         regthickness(ireg)=frontgap(ireg)+midgap(ireg)+
     $        backgap(ireg)+21.*dlayer(isup1)+21.*dlayer(isup2)
      enddo
c
c LOOP OVER SUPERLAYERS
c
      itest=0
      do isup=1,6
         sup=float(isup)
c     calculate some commonly used expressions
         ctilt=cos(thtilt(isup)/degrad)
         stilt=sin(thtilt(isup)/degrad)
         cster=cos(thster(isup)/degrad)
         sster=sin(thster(isup)/degrad)
c     dw is the characteristic distance between sense wires
         dw=dlayer(isup)*4.*cos(30./degrad)
c     
c     dw2 is the distance between the wire 'mid-points' (which are the 
c     intersections of the wires with the chamber mid-plane) in each layer
c     
         dw2=dw/cster
c     calculate wire direction cosines
         cwire(1)=-sster*ctilt
         cwire(2)=cster
         cwire(3)=sster*stilt
c     
c     calculate direction cosines of wire planes
         cplane(1)=stilt
         cplane(2)=0.
         cplane(3)=ctilt
c     
c     calculate direction cosines of right-hand endplate
         crhplate(1)=sin(thopen(isup)/2./degrad)
         crhplate(2)=-cos(thopen(isup)/2./degrad)
         crhplate(3)=0.
c     
c     calculate direction cosines of left-hand endplate
         clhplate(1)=sin(thopen(isup)/2./degrad)
         clhplate(2)=cos(thopen(isup)/2./degrad)
         clhplate(3)=0.
c     
c     input a common point on the right-hand and left-hand endplate
c     - we have chosen a point at y,z =0; i.e. the x-distance from the
c     beamline to the intersection line of the two endplates
         xplates(1)=xoffset(isup)
         xplates(2)=0.
         xplates(3)=0.
c
c     now, calculate the midpoint posn. of the first guard wire in
c     the first guard layer, using the angle, thmin, as defined for
c     the "ifirstwir" guard wire in that superlayer 
c     where "mid-point" is the intersection of the first wire w/ the mid-plane
c
c  What is the FIRST WIRE?
c  X0mid is the position of the first GUARD WIRE in the first GUARD WIRE LAYER.
c  the one whose "mid-point" is at a polar angle of THMIN;
c  in the first layer which is a GUARD WIRE LAYER.
c  ifirstwir(sup) is the integer marker of which wire this is
c
         r=dist2tgt(isup)
         dist1mid=r/cos((thtilt(isup)-thmin(isup))/degrad)
         x0mid=dist1mid*sin(thmin(isup)/degrad)-
     $        float(ifirstwir(isup)-1)*dw2*ctilt
         y0mid=0.
         z0mid=dist1mid*cos(thmin(isup)/degrad)+
     $        float(ifirstwir(isup)-1)*dw2*ctilt
c     calculate the thickness of a geant4 "layer"; where a geant4 layer
c     is 3 layer thicknesses
         lyrthick=layerthickness(isup)
c     
c     LOOP OVER LAYERS (22 layers; 1 guard, 6 sense, 1 guard with 14 field
c      interspersed
c
         do ilayer=1,22
            layer=float(ilayer)
c for each sense layer, give it the sense layer number
         isenselayer=-1
            if(mod((ilayer-1),3).eq.0) then
               isenselayer=(ilayer-1)/3
            endif
c     first, calculate the distance to the layer in question from the 
c     first layer
            r=(layer-1.)*dlayer(isup)
c     now, calculate the midpoint posn. of the 1st wire in the layer
c     where "mid-point" is the intersection of the first wire w/ the mid-plane
         x1mid=x0mid+stilt*r
         y1mid=0.
         z1mid=z0mid+ctilt*r
c     now, put in the "brick-wall" stagger: layer-to-layer; each even
c      numbered layer is moved out (to larger x) a half-cell
         if(((ilayer/2)*2).eq.ilayer) then
            x1mid=x1mid+0.5*dw2*ctilt
            y1mid=0.
            z1mid=z1mid-0.5*dw2*stilt
         endif
c put in  ministagger, but only for sense layers
         if(isenselayer.ne.-1) then
c ministagger goes 'in' (smaller x) for odd sense layers
            if(((isenselayer/2)*2).ne.isenselayer) then
               x1mid=x1mid-ministagger(isup)*ctilt
               y1mid=0.
               z1mid=z1mid+ministagger(isup)*stilt
            else
               x1mid=x1mid-ministagger(isup)*ctilt
               y1mid=0.
               z1mid=z1mid+ministagger(isup)*stilt
            endif
         endif
c     
c     LOOP OVER WIRES (in each layer, 1 guard, 112 sense, 1 guard)
c     
         isensewir=-1
            do iwir=1,114
c
c  now calculate the sense wire number (1 - 112)
c  do only for the valid sense layers
c
c  ------------------------------------------------------
               if(isenselayer.ne.-1) then
                  isensewir=iwir-1
                  if(isensewir.eq.0.or.isensewir.eq.113) then
                     isensewir=-1
                  endif
               endif
c  ---------------------------------------------------------
c
               wir=float(iwir)
c     
c     xmid,ymid,zmid are the wire "mid-points"
            xmid(1,iwir)=x1mid+(iwir-1)*dw2*ctilt
            xmid(2,iwir)=0.
            xmid(3,iwir)=z1mid-(iwir-1)*dw2*stilt
c     angmid is the polar angle to the wire mid-point
               angmid(iwir)=atan(xmid(1,iwir)/xmid(3,iwir))*degrad
c     
c     find the intersection of line with a plane and the distance
c     to the plane; first load 3-vectors
               do i=1,3
                  xmidwire(i)=xmid(i,iwir)
               enddo
c     call intersection finder (for right and left plates)
               call lineplaneint(xmidwire,cwire,xplates,crhplate,
     $              wirelenr,xrightwire)
c     
               call lineplaneint(xmidwire,cwire,xplates,clhplate,
     $              wirelenl,xleftwire)
               do i=1,3
                  xright(i,iwir)=xrightwire(i)
                  xleft(i,iwir)=xleftwire(i)
               enddo
c
c     now calculate the total wirelength of each wire
               wirelength(iwir)=abs(wirelenl)+abs(wirelenr)
c     
c     x,y,z of the wire center (not it's "mid-point")
               do i=1,3
               xcenter(i,iwir)=(xleft(i,iwir)+xright(i,iwir))/2.
               enddo
c     
c     now, rotate into endplate coord. system
c     thopen/2 is the angle from mid-plane to endplate plane
               c=cos(thopen(isup)/2./degrad)
               s=sin(thopen(isup)/2./degrad)
c     
c     by definition xplates(1) is the x-distance between the beam line and
c     the line of intersection of the right and left-hand endplates
c     by definition, xplates(2) and xplates(3) are 0.
               x=xright(1,iwir)-xplates(1)
               y=xright(2,iwir)-xplates(2)
               z=xright(3,iwir)-xplates(3)
c     xrtpl,yrtpl,zrtpl are the wire locations in the right endplate plane
c     in this plane, y=0
               xrtpl=c*x-s*y
               yrtpl=s*x+c*y
               zrtpl=z
c     plane is a test result; it should equal 0 if x,y,z in a plane
               plane=crhplate(1)*x+crhplate(2)*y+crhplate(3)*z
c          
c     by definition xplates(1) is the x-distance between the beam line and
c     the line of intersection of the right and left-hand endplates
c     by definition, xplates(2) and xplates(3) are 0.
               x=xleft(1,iwir)-xplates(1)
               y=xleft(2,iwir)-xplates(2)
               z=xleft(3,iwir)-xplates(3)
c     xlfpl,ylfpl,zlfpl are the wire locations in the left endplate plane
c     in this plane, y=0
               xlfpl=c*x+s*y
               ylfpl=-s*x+c*y
               zlfpl=z
c     plane is a test result; it should equal 0 if x,y,z in a plane
               plane=clhplate(1)*x+clhplate(2)*y+clhplate(3)*z
c  ----------------------------------------------------------------------
c     print out information on the "edge" sense wires
      if(isenselayer.eq.1.or.isenselayer.eq.2.or.isenselayer.eq.5.or.
     $              isenselayer.eq.6) then
          if(isensewir.eq.1.or.isensewir.eq.112) then
       print 100,isup,isenselayer,isensewir,xmid(1,iwir),xmid(2,iwir),
     $            xmid(3,iwir),xleft(1,iwir),xleft(2,iwir),
     $            xleft(3,iwir),xright(1,iwir),xright(2,iwir),
     $            xright(3,iwir)
 100       format('sup,lay,wir,xmid,xleft,xright',3i4,9f9.3)
          endif
       endif
c ------------------------------------------------------------------------
c
            enddo     !wire do-loop

c ----------------------------------------------------------

c calculate the parameters for each layer's trapezoid  ----
c One layer of sense wires lies in a trapezoidal volume
c The trapezoidal volume has two trapezoidal faces and
c four rectangular faces.  The front and back trapezoidal
c faces are in planes which are parallel to the sense wire
c plane and equidistant from it.  The distance between
c the trapezoidal planes is the thickness in z.
c "x" is in the wire direction and "y" is perpendicular
c to the wire direction, but in the wire plane.
c To summarize "z_trap" is parallel to a 25 deg. ray from
c the target, "x_trap" is parallel to the wires.
c The y_trap extent of the trapezoid goes from guard wire
c to guard wire; 113 wire-gaps in total (2 guard wires, 112
c sense wires).  The smaller "x_trap" side is the length of
c the short guard wire, and the larger is the length of the
c long guard wire.


c     calculate the short and long "x" lengths
            delx1lyr(isup,ilayer)=wirelength(1)/2.
            delx2lyr(isup,ilayer)=wirelength(114)/2.
c     calculate the "y" length of the layer trapezoid
            do i=1,3
               xpoint1(i)=xcenter(i,1)
               xpoint2(i)=xcenter(i,114)
            enddo
c     plane is a test result; it should equal 0 if x,y,z in a plane
            plane=0
            do i=1,3
               plane=plane+cplane(i)*(xcenter(i,1)-xcenter(i,114))
            enddo
c -----------------------------------------------------------------
c calculate the separation between parallel wires       ---------
c     inputs: a point from each wire, their dir. cosine
c     output: the distance between wires and the intersection on wire2
            call wiretowire(xpoint1,xpoint2,cwire,wir2wir,xpoint3)
            wirespan(isup,ilayer)=wir2wir
            delylyr(isup,ilayer)=wir2wir/2.
c calculate the angle between the perp. line (x1-x3) and the line
c  joining the centers, (x1-x2)
            call anglepoint(xpoint1,xpoint2,xpoint3,angle)
            lyrangle(isup,ilayer)=angle
c now calculate the "middle" of the layer trapezoid
            do i=1,3
               xlyr(i,isup,ilayer)=(xcenter(i,1)+xcenter(i,114))/2.
            enddo
c ---------------------------------------------------------------
c print out the layer trapezoid's parameters

               ifirst=ifirst+1
c               if(ifirst.eq.1) then
c                  print *,"sup,lyr,delx1-x2-y,angle,thk"
c               endif
c            print *,isup,ilayer,delx1lyr(isup,ilayer),
c     $              delx2lyr(isup,ilayer),delylyr(isup,ilayer),
c     $              angle,layerthickness(isup)
c ---------------------------------------------------------------
c calculate the base-length of the "mother volume" trapezoid ----
c I know that the wire end point that is closest to the beam line
c is from superlayer 1, layer 1, wire 1 on the left endplate.
c I also know that the wire end point that is farthest from
c the beam line is for superlayer 2, layer 22, wire 114
c I use these points as two of the eight corners of the
c generalized trapezoid that is the mother volume.
c I get the other parameters by symmetry
c
c     calculate the region from the superlayer
            ireg=1+(isup-1)/2
c     figure out whether it's the 1st or 2nd superlayer in the region
         isup1=2*ireg-1
         isup2=isup1+1
c the short side of the trapezoid
            if(isup.eq.isup1.and.ilayer.eq.1) then
               delx1=xleft(2,1)
               xx1=xleft(1,1)
               xz1=xleft(3,1)
            endif
c the long side of the trapezoid
            if(isup.eq.isup2.and.ilayer.eq.22) then
               delx2=xleft(2,114)
               xx2=xleft(1,114)
               xz2=xleft(3,114)
            endif      
c -----------------------------------------------------------------
         enddo      !layer do-loop
         dely=(xx2-xx1)/cos(thtilt(isup)/degrad)/2.
c ------------------------------------------------------------------
         if(isup.eq.isup2) then
c   calculate the x,y,z of the center of the mother volume
            center_m(1,ireg)=(xx1+xx2)/2.
            center_m(2,ireg)=0.
            center_m(3,ireg)=(xz1+xz2)/2.
c
c     print out the mother volume trapezoid's parameters
c            print *,"ireg,delx1,delx2,dely,thickness,x,y,z",
c     $           ireg,delx1,delx2,dely,regthickness(ireg),
c     $           center_m(1,ireg),center_m(2,ireg),
c     $           center_m(3,ireg)
         endif
      enddo     !super-layer do-loop
c  -------------------------------------------------------------------
c   now calculate the position of the layer vols. wrt mother volume
      do isup=1,6
         ctilt=cos(thtilt(isup)/degrad)
         stilt=sin(thtilt(isup)/degrad)
         ireg=1+(isup-1)/2
c     figure out whether it's the 1st or 2nd superlayer in the region
         isup1=2*ireg-1
         isup2=isup1+1
         do ilayer=1,22
c     calculate distance in sector coord. system
            dx=xlyr(1,isup,ilayer)-center_m(1,ireg)
            dy=xlyr(2,isup,ilayer)-center_m(2,ireg)
            dz=xlyr(3,isup,ilayer)-center_m(3,ireg)
            sum1=dx**2+dy**2+dz**2
c     now rotate to the mother coordinate system
c      and interchange "x" and "y"
            delxlyr(1,isup,ilayer)=dy
            delxlyr(2,isup,ilayer)=ctilt*dx-stilt*dz
            delxlyr(3,isup,ilayer)=ctilt*dz+stilt*dx
            sum2=0.
            do i=1,3
               sum2=sum2+(delxlyr(i,isup,ilayer))**2
            enddo
c            print *,"sum1,sum2",sum1,sum2
c            print *,"lyr placement in mother coord's",
c     $           delxlyr(1,isup,ilayer),delxlyr(2,isup,ilayer),
c     $           delxlyr(3,isup,ilayer)
         enddo
      enddo
      stop
      end
c ------------------------------------------------------------------
c     subroutine intersection finder

               subroutine lineplaneint(xwire,cwire,xplates,cplate,
     $              wirelen,xintersection)
               implicit none
               integer i
c  input: point on the wire, wire direction, point on the plate, plate normal
               real xwire(3),cwire(3),xplates(3),cplate(3)
c  output: length from wire point to intersection, and intersection point
               real wirelen,xintersection(3)
c  assorted temporary variables
               real numx,numy,numz,denomx,denomy,denomz
c     solve 4 eqns (3 line eqs., 1 plane eq.) for 4 quantities:
c     the 3 intersection points and the line length
               numx=cplate(1)*(xwire(1)-xplates(1))
               numy=cplate(2)*(xwire(2)-xplates(2))
               numz=cplate(3)*(xwire(3)-xplates(3))
c     
               denomx=cwire(1)*cplate(1)
               denomy=cwire(2)*cplate(2)
               denomz=cwire(3)*cplate(3)
c     
c     wire length from mid-point to plane
               wirelen=-(numx+numy+numz)/(denomx+denomy+denomz)
c     
c     x,y,z intersection of wire with plane
               xintersection(1)=xwire(1)+wirelen*cwire(1)
               xintersection(2)=xwire(2)+wirelen*cwire(2)
               xintersection(3)=xwire(3)+wirelen*cwire(3)
c
               return
               end
c ----------------------------------------------------------------
      subroutine wiretowire(x1,x2,cwire,wir2wir,x3)
c      calculate distance between parallel wires
c       where x1,x2 are points on the two wires
c       wiretowire is the distance between wires, x3 is the
c       point on wire 2 closest to x1 (pt. on wire 1)
      implicit none
      real x1(3),x2(3),x3(3),cwire(3)
      real wir2wir,delta
      integer i
c -------------------------------
      delta=0.
      do i=1,3
         delta=delta+cwire(i)*(x1(i)-x2(i))
      enddo
      do i=1,3
         x3(i)=x2(i)+cwire(i)*delta
      enddo
      wir2wir=0.
      do i=1,3
         wir2wir=wir2wir+(x3(i)-x1(i))**2
      enddo
      wir2wir=sqrt(wir2wir)
      return
      end
c -------------------------------------------------------------------
      subroutine anglepoint(x1,x2,x3,angle)
c routine which calculates the angle between the vectors (x1-x2) and
c  (x1-x3)
c  angle in degrees
      implicit none
      real x1(3),x2(3),x3(3),angle
      real x1x2norm,x1x3norm,dot,cosine
      integer i
      real degrad
      data degrad/57.2957795/
c first calculate norms of vectors
      x1x2norm=0.
      x1x3norm=0.
      do i=1,3
         x1x2norm=x1x2norm+(x1(i)-x2(i))**2
         x1x3norm=x1x3norm+(x1(i)-x3(i))**2
      enddo
      x1x2norm=sqrt(x1x2norm)
      x1x3norm=sqrt(x1x3norm)
c     now do dot product
      dot=0.
      do i=1,3
         dot=dot+(x1(i)-x2(i))*(x1(i)-x3(i))
      enddo
      cosine=dot/x1x2norm/x1x3norm
c     now calculate angle in degrees
      angle=acos(cosine)*degrad
c Yelena tells me that my sign convention was wrong
c      angle=angle*(x3(2)-x2(2))/abs(x3(2)-x2(2))
      angle=angle*(x2(2)-x3(2))/abs(x2(2)-x3(2))
      return
      end

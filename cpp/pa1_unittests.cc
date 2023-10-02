#include <gtest/gtest.h>
#include "utils.h"
#include "vec3.h"
#include "color.h"
#include "interval.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream

namespace {
	TEST(Vec3Test,BasicFuncs){
		vec3 a = vec3(0,0,0);
		EXPECT_EQ(0,a.x());
		EXPECT_EQ(0,a.y());
		EXPECT_EQ(0,a.z());
		
		vec3 b = vec3(1.2,3.45,3.3);
		EXPECT_EQ(1.2,b.x());
		EXPECT_EQ(3.45,b.y());
		EXPECT_EQ(3.3,b.z());
	}


	TEST(Vec3Test,BasicAdd){
		vec3 a = vec3(1,2,3);
		vec3 b = vec3(3,4,5);
		vec3 c = a+b;
		vec3 d = b+a;
		EXPECT_EQ(4,c.x());
		EXPECT_EQ(6,c.y());
		EXPECT_EQ(8,c.z());
		
		EXPECT_EQ(4,d.x());
		EXPECT_EQ(6,d.y());
		EXPECT_EQ(8,d.z());
	}

	TEST(Vec3Test,BasicSubtract){
		vec3 a = vec3(1,2,3);
		vec3 b = vec3(3,4,5);
		vec3 c = a-b;
		vec3 d = b-a;
		EXPECT_EQ(-2,c.x());
		EXPECT_EQ(-2,c.y());
		EXPECT_EQ(-2,c.z());
		
		EXPECT_EQ(2,d.x());
		EXPECT_EQ(2,d.y());
		EXPECT_EQ(2,d.z());
	}


	TEST(Vec3Test,ScalarMultiple){
		vec3 a = vec3(1,2,3);
		double b = 5.0; 
		vec3 c = 5*a;
		vec3 d = a*5;
		EXPECT_EQ(5,c.x());
		EXPECT_EQ(10,c.y());
		EXPECT_EQ(15,c.z());
		
		EXPECT_EQ(5,d.x());
		EXPECT_EQ(10,d.y());
		EXPECT_EQ(15,d.z());
	}


	TEST(Vec3Test,DotProduct){
		vec3 a = vec3(1,2,3);
		vec3 b = vec3(3,4,5);
		double c = dot(a,b);
		double d = dot(b,a);
		EXPECT_EQ(26,c);
		EXPECT_EQ(26,d);
	}

	TEST(Vec3Test,CrossProduct){
		vec3 a = vec3(1,2,3);
		vec3 b = vec3(3,4,5);
		vec3 c = cross(a,b);
		vec3 d = cross(b,a); 
		EXPECT_EQ(-2,c.x());
		EXPECT_EQ(4,c.y());
		EXPECT_EQ(-2,c.z());
		
		EXPECT_EQ(2,d.x());
		EXPECT_EQ(-4,d.y());
		EXPECT_EQ(2,d.z());
	}


	TEST(Vec3Test,Length){
		vec3 a = vec3(1,2,3);
		double b = a.length(); 
		EXPECT_EQ(sqrt(14),b);
	}


	TEST(Vec3Test,UnitVec){
		vec3 a = vec3(1,2,3);
		vec3 b = unit_vector(a); 
		EXPECT_EQ(1/sqrt(14),b.x());
		EXPECT_EQ(2/sqrt(14),b.y());
		EXPECT_EQ(3/sqrt(14),b.z());
	}

	
	TEST(Vec3Test,RandUnitDisk){
		vec3 a = random_in_unit_disk(); 
		EXPECT_EQ(a.z(),0);
		EXPECT_LT(a.length(),1);
	}


	TEST(Vec3Test,RandUnitSphere){
		vec3 a = random_in_unit_sphere(); 
		vec3 b = random_in_unit_sphere(); 
		EXPECT_LT(a.length(),1);
		EXPECT_LT(b.length(),1);
		EXPECT_NE(a.x(),b.x());
		EXPECT_NE(a.y(),b.y());
		EXPECT_NE(a.z(),b.z());
	}

	TEST(Vec3Test,RandUnitVec){
		vec3 a = random_unit_vector(); 
		vec3 b = random_unit_vector(); 
		EXPECT_DOUBLE_EQ(a.length(),1);
		EXPECT_DOUBLE_EQ(b.length(),1);
		EXPECT_NE(a.x(),b.x());
		EXPECT_NE(a.y(),b.y());
		EXPECT_NE(a.z(),b.z());
	}
	
	TEST(Vec3Test,RandUnitHemi){
		vec3 normal = vec3(0,0,1);
		vec3 a = random_on_hemisphere(normal);
		vec3 b = random_on_hemisphere(normal);
		double resa = dot(a,normal);
		double resb = dot(b,normal);
		EXPECT_GT(resa,0);
		EXPECT_GT(resb,0);
		EXPECT_LT(a.length_squared(),1);
		EXPECT_LT(a.length_squared(),1);
		EXPECT_NE(a.x(),b.x());
		EXPECT_NE(a.y(),b.y());
		EXPECT_NE(a.z(),b.z());
	}


	TEST(Vec3Test,Reflection){
		vec3 a = vec3(1,2,3); 
		vec3 b = vec3(2,2,2);
		vec3 res = reflect(a,b);
		vec3 man = a-2*dot(a,b)*b;
		EXPECT_EQ(res.x(),man.x());
		EXPECT_EQ(res.y(),man.y());
		EXPECT_EQ(res.z(),man.z());
	}


	TEST(Vec3Test,Refraction){
		vec3 v = vec3(1,2,3);
		vec3 uv = unit_vector(v);
		vec3 norm = vec3(2,2,2);
		vec3 unitnorm = unit_vector(norm);
		double ratio = 1.2;
		vec3 res = refract(uv,unitnorm,ratio);
		vec3 man =vec3(-0.8352636868373895,  -0.51455019654248013, -0.19383670624757088); 
		EXPECT_DOUBLE_EQ(res.x(),man.x());
		EXPECT_DOUBLE_EQ(res.y(),man.y());
		EXPECT_DOUBLE_EQ(res.z(),man.z());
	}


	TEST(ColorTest,WriteColor){
		color c = color(0.2,0.5,0.2);
		std::ostringstream s = std::ostringstream();
		write_color(s,c,1);
		std::string s2 = "114 181 114\n";
		std::string res = s.str();
		EXPECT_EQ(res,s2);
	}


	TEST(RayTest,Constructor){
		point3 origin = point3(1,1,1);
		vec3 direction = vec3(1,7,8);
		ray r = ray(origin,direction);

		EXPECT_DOUBLE_EQ(r.origin().x(),origin.x());
		EXPECT_DOUBLE_EQ(r.origin().y(),origin.y());
		EXPECT_DOUBLE_EQ(r.origin().z(),origin.z());

		EXPECT_DOUBLE_EQ(r.direction().x(),direction.x());
		EXPECT_DOUBLE_EQ(r.direction().y(),direction.y());
		EXPECT_DOUBLE_EQ(r.direction().z(),direction.z());
	}

	TEST(RayTest,AT){
		point3 origin = point3(1,1,1);
		vec3 direction = vec3(1,7,8);
		ray r = ray(origin,direction);
		point3 p = r.at(2);
		EXPECT_DOUBLE_EQ(p.x(),3);
		EXPECT_DOUBLE_EQ(p.y(),15);
		EXPECT_DOUBLE_EQ(p.z(),17);


	}


	TEST(IntervalTest,IConstructor){
		interval i = interval(-1,1);
		EXPECT_DOUBLE_EQ(i.min,-1);
		EXPECT_DOUBLE_EQ(i.max,1);

	}

	TEST(IntervalTest,ISurrounds){
		interval i = interval(-1,1);
		EXPECT_TRUE(i.surrounds(0));
		EXPECT_FALSE(i.surrounds(-2));
		EXPECT_FALSE(i.surrounds(2));
		EXPECT_FALSE(i.surrounds(1));
		EXPECT_FALSE(i.surrounds(-1));

	}

	TEST(IntervalTest,IContains){
		interval i = interval(-1,1);
		EXPECT_TRUE(i.contains(0));
		EXPECT_FALSE(i.contains(-2));
		EXPECT_FALSE(i.contains(2));
		EXPECT_TRUE(i.contains(1));
		EXPECT_TRUE(i.contains(-1));

	}


	TEST(InteralTest,ISize){
		interval i = interval(-1,1);
		EXPECT_DOUBLE_EQ(i.size(),2.0);
	}


	TEST(InteralTest,IExpand){
		interval i = interval(-1,1);
		interval j = i.expand(2.0);
		EXPECT_DOUBLE_EQ(j.min,-2.0);
		EXPECT_DOUBLE_EQ(j.max,2.0);
	}
	
	TEST(InteralTest,IEmpty){
		interval i = interval::empty;
		EXPECT_DOUBLE_EQ(i.min,+infinity);
		EXPECT_DOUBLE_EQ(i.max,-infinity);
	}

	TEST(InteralTest,IAll){
		interval i = interval::universe;
		EXPECT_DOUBLE_EQ(i.min,-infinity);
		EXPECT_DOUBLE_EQ(i.max,+infinity);
	}


	TEST(HitRecordTest,PointSet){
		vec3 direct = vec3(1,7,8);
		vec3 orig = vec3(1,1,1);
		ray r = ray(orig,direct);
		point3 p = r.at(1);
		hit_record record = hit_record();
		record.p = p;
		record.t = 1;
		EXPECT_DOUBLE_EQ(record.p.x(),p.x());
		EXPECT_DOUBLE_EQ(record.p.y(),p.y());
		EXPECT_DOUBLE_EQ(record.p.z(),p.z());
		EXPECT_DOUBLE_EQ(record.t,1);
	}

	TEST(HitRecordTest,SetFaceNormal){
		vec3 direct = vec3(1,7,8);
		vec3 orig = vec3(1,1,1);
		ray r = ray(orig,direct);
		vec3 norm = unit_vector(vec3(0,1,0));
		point3 p = r.at(3.2);
		hit_record record = hit_record();
		record.p = p;
		record.t = 3.2;
		record.set_face_normal(r,norm);
		EXPECT_DOUBLE_EQ(record.normal.x(),-norm.x());
		EXPECT_DOUBLE_EQ(record.normal.y(),-norm.y());
		EXPECT_DOUBLE_EQ(record.normal.z(),-norm.z());
	

		orig = vec3(1,1,1);
		r = ray(orig,direct);
		norm = unit_vector(vec3(0,-1,0));
		p = r.at(3.2);
		record = hit_record();
		record.p = p;
		record.t = 3.2;
		record.set_face_normal(r,norm);
		EXPECT_DOUBLE_EQ(record.normal.x(),norm.x());
		EXPECT_DOUBLE_EQ(record.normal.y(),norm.y());
		EXPECT_DOUBLE_EQ(record.normal.z(),norm.z());

	}



	TEST(SphereHitTest,Hit){

		sphere s = sphere(point3(0,-1,0),10);
		vec3 direct = vec3(1,7,8);
		point3 orig = point3(1,1,1);	
		ray r = ray(orig,direct);
		interval i = interval(0,10);
		hit_record record = hit_record();
		bool wasHit = s.hit(r,i,record);
		EXPECT_TRUE(wasHit);
		EXPECT_DOUBLE_EQ(0.72844249414426698,record.t);

	}


	TEST(SphereHitTest,Miss){

		sphere s = sphere(point3(0,-1,0),10);
		vec3 direct = vec3(1,7,8);
		point3 orig = point3(20,20,20);	
		ray r = ray(orig,direct);
		interval i = interval(0,10);
		hit_record record = hit_record();
		bool wasHit = s.hit(r,i,record);
		EXPECT_FALSE(wasHit);


	}

	TEST(SphereHitTest,MissOutInterval){

		sphere s = sphere(point3(0,-1,0),10);
		vec3 direct = vec3(1,7,8);
		point3 orig = point3(1,1,1);	
		ray r = ray(orig,direct);
		interval i = interval(0,0.2);
		hit_record record = hit_record();
		bool wasHit = s.hit(r,i,record);
		EXPECT_FALSE(wasHit);


	}

	TEST(HitListTest,AddObject){
		hittable_list hitlist = hittable_list();
		hitlist.add(make_shared<sphere>(point3(0,-1,0),12));
		hitlist.add(make_shared<sphere>(point3(-20,-1,0),12));
		EXPECT_EQ(hitlist.objects.size(),2);
	}
	

	TEST(HitListTest,Removed){
		hittable_list hitlist = hittable_list();
		hitlist.add(make_shared<sphere>(point3(0,-1,0),12));
		hitlist.add(make_shared<sphere>(point3(-20,-1,0),12));
		hitlist.clear();
		EXPECT_EQ(hitlist.objects.size(),0);
	}
	
	TEST(HitListTest,HitList){
		hittable_list hitlist = hittable_list();
		hitlist.add(make_shared<sphere>(point3(0,-1,0),10));
		hitlist.add(make_shared<sphere>(point3(100,100,100),1));
		
		vec3 direct = vec3(1,7,8);
		point3 orig = point3(1,1,1);	
		ray r = ray(orig,direct);
		interval i = interval(0,10);
		hit_record record = hit_record();

		bool wasHit = hitlist.hit(r,i,record);
		EXPECT_TRUE(wasHit);
		EXPECT_DOUBLE_EQ(0.72844249414426698,record.t);
	}


}



int main(int argc, char **argv) {
  printf("Running main() from %s\n", __FILE__);
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

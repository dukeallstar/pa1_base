import unittest
from vec3 import vec3
import numpy as np
from color import color
from vec3 import vec3 as point3
from ray import ray
from interval import interval
from hittable import sphere
from hittable_list import hittable_list

class TestVec3(unittest.TestCase):
    def test_constructor(self):
        a=vec3(0,0,0)
        self.assertEqual(a.e[0],0)
        self.assertEqual(a.e[1],0)
        self.assertEqual(a.e[2],0)

        a=vec3(2.0,3.123,42.19)
        self.assertEqual(a.e[0],2.0)
        self.assertEqual(a.e[1],3.123)
        self.assertEqual(a.e[2],42.19)

    def test_xyz(self):
        a=vec3(1,3,4)
        self.assertEqual(a.x(),1)
        self.assertEqual(a.y(),3)
        self.assertEqual(a.z(),4)

    def test_add(self):
        a = vec3(1,2,3)
        b = vec3(3,4,5)
        c = a+b
        self.assertEqual(c.x(),4)
        self.assertEqual(c.y(),6)
        self.assertEqual(c.z(),8)

        d = b+a
        self.assertEqual(d.x(),4)
        self.assertEqual(d.y(),6)
        self.assertEqual(d.z(),8)


    def test_subtract(self):
        a = vec3(1,2,3)
        b = vec3(3,4,5)
        c = a-b
        self.assertEqual(c.x(),-2)
        self.assertEqual(c.y(),-2)
        self.assertEqual(c.z(),-2)

        d = b-a
        self.assertEqual(d.x(),2)
        self.assertEqual(d.y(),2)
        self.assertEqual(d.z(),2)

    def test_scalarmultiple(self):
        a = vec3(1,2,3)
        b = 5 
        c = 5*a
        self.assertEqual(c.x(),5)
        self.assertEqual(c.y(),10)
        self.assertEqual(c.z(),15)

        d = a*5
        self.assertEqual(d.x(),5)
        self.assertEqual(d.y(),10)
        self.assertEqual(d.z(),15)


    def test_dot(self):
        a = vec3(1.0,2,3.0)
        b = vec3(3,4.0,5)
        c = a.dot(b)
        self.assertEqual(c,26)

        d= b.dot(a)
        self.assertEqual(d,26)


    def test_crossproduct(self):
        a = vec3(1.0,2,3.0)
        b = vec3(3,4.0,5)
        c = a.cross(b)
        self.assertEqual(c.x(),-2)
        self.assertEqual(c.y(),4)
        self.assertEqual(c.z(),-2)

        d = b.cross(a)
        self.assertEqual(d.x(),2)
        self.assertEqual(d.y(),-4)
        self.assertEqual(d.z(),2)


    def test_length(self):
        a = vec3(1.0,2,3.0)
        b= a.length()
        self.assertEqual(b,np.sqrt(14))


    def test_unitvect(self):
        a = vec3(1.0,2,3.0)
        b= a.unit_vector()
        self.assertEqual(b.x(),1/np.sqrt(14))
        self.assertEqual(b.y(),2/np.sqrt(14))
        self.assertEqual(b.z(),3/np.sqrt(14))

    def test_unitdisk(self):
        a = vec3.rand_in_unit_disk()
        self.assertEqual(a.z(),0)
        self.assertLess(a.length_squared(), 1)


    def test_unitsphere(self):
        a = vec3.rand_in_unit_sphere()
        b = vec3.rand_in_unit_sphere()
        self.assertLess(a.length_squared(), 1)
        self.assertLess(b.length_squared(), 1)
        self.assertNotEqual(a.x(),b.x())
        self.assertNotEqual(a.y(),b.y())
        self.assertNotEqual(a.z(),b.z())

    def test_randunitvect(self):
        a = vec3.rand_unit_vector()
        b = vec3.rand_unit_vector()
        self.assertAlmostEqual(a.length_squared(), 1)
        self.assertAlmostEqual(b.length_squared(),1)
        self.assertNotEqual(a.x(),b.x())
        self.assertNotEqual(a.y(),b.y())
        self.assertNotEqual(a.z(),b.z())

    def test_rand_on_hemisphere(self):
        normal = vec3(0,0,1)
        a = vec3.rand_on_hemisphere(normal)
        b = vec3.rand_unit_vector(normal)
        resa = a.dot(normal)
        resb = b.dot(normal)
        self.assertGreater(resa,0)
        self.assertGreater(resb,0)
        self.assertLess(a.length_squared(), 1)
        self.assertLess(b.length_squared(), 1)
        self.assertNotEqual(a.x(),b.x())
        self.assertNotEqual(a.y(),b.y())
        self.assertNotEqual(a.z(),b.z())

    def test_reflect(self):
        a = vec3(1,2,3)
        b = vec3(2,2,2)
        res = vec3.reflect(a,b)
        man = a-2*a.dot(b)*b
        self.assertEqual(res.x(),man.x())
        self.assertEqual(res.y(),man.y())
        self.assertEqual(res.z(),man.z())

    
    def test_refract(self):
        v = vec3(-1,-2,-3)
        uv = v.unit_vector()
        normal = vec3(2,2,2)
        unit_normal = normal.unit_vector()
        eta_ratio = 1.2
        res = vec3.refract(uv,unit_normal,eta_ratio)
        man = vec3(-0.8352636868373895, -0.51455019654248013, -0.19383670624757088)
        self.assertAlmostEqual(res.x(),man.x())
        self.assertAlmostEqual(res.y(),man.y())
        self.assertAlmostEqual(res.z(),man.z())


    def test_write_color(self):
        a = color(0.2,0.5,0.2)
        f = a.write_color()
        self.assertEqual(f,"114 181 114")



class TestRays(unittest.TestCase):

    def test_construct(self):
        direct = vec(1,7,8)
        orig = vec(1,1,1)
        a = ray(orig,direct)
        self.assertEqual(a.orig.x(),orig.x())
        self.assertEqual(a.orig.y(),orig.y())
        self.assertEqual(a.orig.z(),orig.z())
        self.assertEqual(a.direction.x(),direct.x())
        self.assertEqual(a.direction.y(),direct.y())
        self.assertEqual(a.direction.z(),direct.z())

    def test_at(self):
        direct = vec(1,7,8)
        orig = vec(1,1,1)
        a = ray(orig,direct)
        at = a.at(2)
        self.assertEqual(at.x(),3)
        self.assertEqual(at.y(),15)
        self.assertEqual(at.z(),17)


class TestInterval(unittest.TestCase):
    
    def test_construct(self):
        a = interval(-1,1)
        self.assertEqual(a.min,-1)
        self.assertEqual(a.max,1)

    def test_surrounds(self):
        a = interval(-1,1)
        self.assertTrue(a.surrounds(0))
        self.assertFalse(a.surrounds(-2))
        self.assertFalse(a.surrounds(2))
        self.assertFalse(a.surrounds(1))
        self.assertFalse(a.surrounds(-1))

    def test_contains(self):
        a = interval(-1,1)
        self.assertTrue(a.contains(0))
        self.assertFalse(a.contains(-2))
        self.assertFalse(a.contains(2))
        self.assertTrue(a.contains(1))
        self.assertTrue(a.contains(-1))


    def test_size(self):
        a = interval(-1,1)
        s = a.size()
        self.assertEqual(s,2.0)

    def test_expand(self):
        a = interval(-1,1)
        b = a.expand(2.0)
        self.assertEqual(a.min,-2.0)
        self.assertEqual(a.max,2.0)

    def test_empty(self):
        a = interval.empty()
        self.assertEqual(a.min,float('inf'))
        self.assertEqual(a.max,float('-inf'))

    def test_all(self):
        a = interval.empty()
        self.assertEqual(a.max,float('inf'))
        self.assertEqual(a.min,float('-inf'))


class TestHitRecord(unittest.TestCase):

    def test_set_point():
        direct = vec3(1,7,8)
        orig = vec3(1,1,1)
        r = ray(orig,direct)
        p = r.at(1)
        record = hit_record()
        record.set_point(p)
        self.assertEqual(record.p.x(),p.x())
        self.assertEqual(record.p.y(),p.y())
        self.assertEqual(record.p.z(),p.z())


    def test_set_t():
        direct = vec3(1,7,8)
        orig = vec3(1,1,1)
        r = ray(orig,direct)
        p = r.at(1)
        record = hit_record()
        record.p = p
        record.t = 1
        self.assertEqual(record.t,1)



    def test_set_face_normal(self):
        direct = vec3(1,7,8)
        orig = vec3(1,1,1)
        r = ray(orig,direct)
        norm = vec3(0,1,0).unit_vector()
        record = hit_record()
        record.p = r.at(3.2)
        record.t = 3.2
        record.set_face_normal(r,norm)
        self.assertTrue(record.front_face)
        self.assertEqual(record.normal.x(),-norm.x())
        self.assertEqual(record.normal.y(),-norm.y())
        self.assertEqual(record.normal.z(),-norm.z())

        direct = vec3(1,1,1)
        orig = vec3(1,1,1)
        r = ray(orig,direct)
        norm = vec3(0,-1,0).unit_vector()
        record = hit_record()
        record.set_point(r.at(3.2))
        record.set_t(3.2)
        record.set_face_normal(r,norm)
        self.assertEqual(record.normal.x(),norm.x())
        self.assertEqual(record.normal.y(),norm.y())
        self.assertEqual(record.normal.z(),norm.z())


class TestSphere(unittest.TestCase):
    
    def test_hit(self):
        s = sphere(point3(0,-1,0),10)
        direct = vec3(1,7,8)
        orig = vec3(1,1,1)
        r = ray(orig,direct)
        i = interval(0,10)
        hit_record,wasHit = s.hit(r,i)
        self.assertEqual(wasHit,True)
        self.assertAlmostEqual(hit_record.t,0.728,places=3)
        

    def test_miss(self):
        s = sphere(point3(0,-1,0),10)
        direct = vec3(1,1,1)
        orig = vec3(20,20,20)
        r = ray(orig,direct)
        i = interval(0,10)
        hit_record,wasHit = s.hit(r,i)
        self.assertEqual(wasHit,False)

    def test_hit_out_of_interval(self):
        s = sphere(point3(0,-1,0),10)
        direct = vec3(1,7,8)
        orig = vec3(1,1,1)
        r = ray(orig,direct)
        i = interval(0,0.2)
        hit_record,wasHit = s.hit(r,i)
        self.assertEqual(wasHit,False)

class TestHittableList(unittest.TestCase):
    
    def test_add_obj(self):
        hitList = hittable_list()
        s = sphere(point3(0,-1,0),12)
        s2 = sphere(point3(-20,-1,0),12)
        hitList.add(s)
        hitList.add(s2)
        self.assertEqual(len(hitList.objects),2)


    def test_clear_obj(self):
        hitList = hittable_list()
        s = sphere(point3(0,-1,0),12)
        s2 = sphere(point3(-20,-1,0),12)
        hitList.add(s)
        hitList.add(s2)
        hitList.clear()
        self.assertEqual(len(hitList.objects),0)

    def test_hit_obj(self):
        hitList = hittable_list()
        s = sphere(point3(0,-1,0),10)
        s2 = sphere(point3(100,100,100),1)
        
        hitList.add(s)
        hitList.add(s2)
        
        direct = vec3(1,7,8)
        orig = vec3(1,1,1)
        r = ray(orig,direct)
        i = interval(0,10)
        
        record,was_hit = hittable_list.hit(r,i) 
        self.assertEqual(wasHit,True)
        self.assertAlmostEqual(hit_record.t,0.72844249414426698,places=3)



if __name__ == '__main__':
    unittest.main()

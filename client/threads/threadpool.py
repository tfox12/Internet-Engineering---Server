from Queue import Queue
from threading import Thread

class WorkerThread(Thread):
	def __init__(self, tasks):
		Thread.__init__(self)
		self.tasks = tasks
		self.daemon = True
		self.start()

	def run(self):
		while True:
		    func, args, kargs = self.tasks.get()
		    try: func(*args, **kargs)
		    except Exception, e: print e
		    self.tasks.task_done()



class ThreadPool:
	def __init__(self, thread_count):
		self.task_queue = Queue(thread_count)
		for _ in range(thread_count): WorkerThread(self.task_queue)
		
	def add_task(self, func, *args, **kargs):
		self.task_queue.put((func, args, kargs))
		
	def wait_for_finish(self):
		self.task_queue.join()
		
		
		
			
	

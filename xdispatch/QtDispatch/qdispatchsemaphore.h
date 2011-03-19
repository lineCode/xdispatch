/*
* Copyright (c) 2011 MLBA. All rights reserved.
*
* @MLBA_OPEN_LICENSE_HEADER_START@
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*     http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
* @MLBA_OPEN_LICENSE_HEADER_END@
*/


#ifndef QDISPATCH_SEMAPHORE_H_
#define QDISPATCH_SEMAPHORE_H_

#include <QDebug>
#include "qdispatchglobal.h"
#include "../dispatch.h"

class QTime;

QT_BEGIN_HEADER
QT_BEGIN_NAMESPACE

QT_MODULE(Dispatch)

/**
  Wraps dispatch semaphores as provided by libDispatch/libXDispatch.

  "A dispatch semaphore is an efficient implementation of a traditional
  counting semaphore. Dispatch semaphores call down to the kernel only
  when the calling thread needs to be blocked. If the calling semaphore
  does not need to block, no kernel call is made."
  */
class QDispatchSemaphore {
	friend QDebug operator<<(QDebug, const QDispatchSemaphore&);

public:
	/**
		Constructs a new semaphore with the given initial value. 
		
		Passing zero for the value is useful for when two threads 
		need to reconcile the completion of a particular event. 
		Passing a value greather than zero is useful for managing 
		a finite pool of resources, where the pool size is equal 
		to the value.

		@remarks Never pass a value less than zero here
		*/
	QDispatchSemaphore(int = 0);
	QDispatchSemaphore(const QDispatchSemaphore&);
	~QDispatchSemaphore();

	/**
		Release the semaphore.

		Increments the counting semaphore. If the previous 
		value was less than zero, this function wakes a
		waiting thread before returning.

		@return non-zero if a thread was woken, zero otherwise.
	*/
	int release();
    /**
        Acquires the semaphore.

        Decrements the counting semaphore. If the value is
        less than zero it will wait until another
        thread released the semaphore.
     */
    void acquire();
	/**
		Tries to acquire the semaphore.

		Decrements the counting semaphore. If the value is
		less than zero it will wait until either another
		thread released the semaphore or the timeout passed.

		@return true if acquiring the semaphore succeeded.
	*/
	bool tryAcquire(dispatch_time_t);
	/**
		Tries to acquire the semaphore.

		Decrements the counting semaphore. If the value is
		less than zero it will wait until either another
		thread released the semaphore or the timeout passed.

		@return true if acquiring the semaphore succeeded.
	*/
	bool tryAcquire(const QTime&);

private:
	class Private;
	Private* d;

};

QDebug operator<<(QDebug, const QDispatchSemaphore&);

QT_END_NAMESPACE
QT_END_HEADER

#endif /* QDISPATCH_SEMAPHORE_H_ */

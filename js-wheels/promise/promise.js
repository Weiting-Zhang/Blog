class _Promise {
  constructor(executor) {
    this.status = 'pending';
    this.onResolveCallBackQueue = [];
    this.onRejectCallBackQueue = [];
    const resolve = value => {
      if (this.status !== 'pending') {
        return;
      }
      this.status = 'resolved';
      this.value = value;
      setTimeout(() => {
        while (this.onResolveCallBackQueue.length) {
          const thenFunc = this.onResolveCallBackQueue.shift();
          thenFunc();
        }
      }, 0);
    };
    const reject = e => {
      if (this.status !== 'pending') {
        return;
      }
      this.status = 'rejected';
      this.reason = e;
      if (!this.onRejectCallBackQueue.length) {
        throw new Error('unhandled promise rejection:' + e);
      }
      setTimeout(() => {
        while (this.onRejectCallBackQueue.length) {
          const catchFunc = this.onRejectCallBackQueue.shift();
          catchFunc();
        }
      }, 0);
    };
    try {
      executor(resolve, reject);
    } catch (e) {
      reject(e);
    }
  }
  static resolve = value => {
    const _promise = new _Promise((res, rej) => {
      res(value);
    });
    return _promise;
  };

  static reject = error => {
    const _promise = new _Promise((res, rej) => {
      rej(error);
    });
    return _promise;
  };
}

_Promise.prototype.then = function then(onFulfilled, onRejected) {
  const callBackFunc = (res, rej) => {
    try {
      const returnValue =
        this.status === 'resolved'
          ? onFulfilled(this.value)
          : onRejected(this.reason);
      if (returnValue && returnValue instanceof _Promise) {
        returnValue.then(
          _r => {
            res(_r);
          },
          _e => {
            rej(_e);
          }
        );
      } else {
        res(returnValue);
      }
    } catch (e) {
      rej(e);
    }
  };

  let thenPromise;
  switch (this.status) {
    case 'pending':
      thenPromise = new _Promise((res, rej) => {
        if (onFulfilled) {
          this.onResolveCallBackQueue.push(() => callBackFunc(res, rej));
        }
        if (onRejected) {
          this.onRejectCallBackQueue.push(() => callBackFunc(res, rej));
        }
      });
      return thenPromise;
    case 'resolved':
    case 'rejected':
      thenPromise = new _Promise((res, rej) => {
        setTimeout(() => callBackFunc(res, rej), 0);
      });
      return thenPromise;
    default:
      break;
  }
};

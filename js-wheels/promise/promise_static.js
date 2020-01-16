Promise._all = promises => {
  const len = promises.length;
  let completed = 0;
  const ans = [];
  return new Promise((resolve, reject) => {
    for (let i = 0; i < promises.length; i++) {
      if (!(promises[i] instanceof Promise)) {
        promises[i] = Promise.resolve(promises[i]);
      }
      promises[i]
        .then(res => {
          completed++;
          ans[i] = res;
          if (completed === len) {
            resolve(ans);
          }
        })
        .catch(e => {
          reject(e);
        });
    }
  });
};

Promise._race = promises => {
  return new Promise((resolve, reject) => {
    for (let i = 0; i < promises.length; i++) {
      if (!(promises[i] instanceof Promise)) {
        promises[i] = Promise.resolve(promises[i]);
      }
      promises[i]
        .then(res => {
          resolve(res);
        })
        .catch(e => {
          reject(e);
        });
    }
  });
};

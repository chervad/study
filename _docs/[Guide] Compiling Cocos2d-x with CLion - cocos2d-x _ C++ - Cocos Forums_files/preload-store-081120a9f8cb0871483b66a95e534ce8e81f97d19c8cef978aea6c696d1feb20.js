define("preload-store",["exports"],function(t){"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.default={data:{},store:function(t,e){this.data[t]=e},getAndRemove:function(t,e){if(this.data[t]){var n=Ember.RSVP.resolve(this.data[t]);return delete this.data[t],n}return e?new Ember.RSVP.Promise(function(t,n){var r=e();r&&r.then?r.then(function(e){return t(e)}).catch(function(t){return n(t)}):t(r)}):Ember.RSVP.resolve(null)},get:function(t){return this.data[t]},remove:function(t){this.data[t]&&delete this.data[t]},reset:function(){this.data={}}}});
//# sourceMappingURL=/assets/preload-store-081120a9f8cb0871483b66a95e534ce8e81f97d19c8cef978aea6c696d1feb20.js.map
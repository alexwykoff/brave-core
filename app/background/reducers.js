/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import {combineReducers} from 'redux'

import shieldsPanelReducer from './reducers/shieldsPanelReducer'
import newTabPageReducer from './reducers/newTabPageReducer'

export default combineReducers({
  shieldsPanel: shieldsPanelReducer,
  newTabPage: newTabPageReducer
})

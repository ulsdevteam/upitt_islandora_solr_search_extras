<?php

/**
 * @file
 * Theme hooks.
 */

function upitt_islandora_solr_search_extras_preprocess_islandora_basic_collection_wrapper(&$variables) {
  dpm('collection wrapper');
  $variables['view_links'] = array();
}

function upitt_islandora_solr_search_extras_preprocess_islandora_basic_collection(&$variables) {
dpm('basic collection');
  $islandora_object = $variables['islandora_object'];
  $variables['view_links'] = array();
  _get_solr_results($islandora_object, $variables);
}

function upitt_islandora_solr_search_extras_preprocess_islandora_basic_collection_list(&$variables) {
dpm('basic collection list');
  $islandora_object = $variables['islandora_object'];
  $variables['view_links'] = array();
  _get_solr_results($islandora_object, $variables);
}

function upitt_islandora_solr_search_extras_preprocess_islandora_basic_collection_grid(&$variables) {
dpm('basic collection grid');
dpm($variables);
  $islandora_object = $variables['islandora_object'];
  $variables['view_links'] = array();
  _get_solr_results($islandora_object, $variables);
}

function upitt_islandora_solr_search_extras_preprocess_islandora_objects_list(&$variables) {
dpm('objects list');
  $islandora_object = menu_get_object('islandora_object', 2);
  _get_solr_results($islandora_object, $variables);
}

function upitt_islandora_solr_search_extras_preprocess_islandora_objects_grid(&$variables) {
dpm('objects grid');
dpm($variables);
  $islandora_object = menu_get_object('islandora_object', 2);
  $variables['view_links'] = array();
  _get_solr_results($islandora_object, $variables);
}

/**
 * Helper function to get the solr search results HTML for the various
 * templates that need it.  This will set the $variables['solr_search'] value.
 *
 * @param type $islandora_object
 * @param array $variables
 */
function _get_solr_results($islandora_object, &$variables) {
  // Inspect the islandora_object to get the PID match for the SOLR query.
  $solr_query = 'RELS_EXT_isMemberOfCollection_uri_ms:"info:fedora/' . $islandora_object->id . '"';
  $markup = islandora_solr($solr_query);
  $content_models = $islandora_object->relationships->get(FEDORA_MODEL_URI, 'hasModel');
  $is_collection = (isset($content_models[0]['object']['value'])) ? ($content_models[0]['object']['value'] == 'islandora:collectionCModel') : FALSE;
  if ($is_collection) {
    _replace_links($islandora_object, $markup);
  }
  $variables['solr_search'] = $markup;
}

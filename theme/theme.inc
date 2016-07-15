<?php

/**
 * @file
 * Theme hooks.
 */

function upitt_islandora_solr_search_extras_preprocess_islandora_objects_subset(&$variables) {
  $variables['display_links'] = array();
  $variables['pager'] = '';
}

function upitt_islandora_solr_search_extras_preprocess_islandora_objects_extras(&$variables) {
//  dpm('islandora objects');
  $variables['theme_hook_suggestions'][] = 'islandora_objects_extras';
  $variables['display_links'] = array();
  $variables['view_links'] = array();
}

function upitt_islandora_solr_search_extras_preprocess_islandora_basic_collection_wrapper(&$variables) {
//  dpm('collection wrapper');
  $variables['view_links'] = array();
$variables['total_count'] = 9099999999999;
}

function upitt_islandora_solr_search_extras_preprocess_islandora_basic_collection(&$variables) {
// dpm('basic collection');
  $islandora_object = $variables['islandora_object'];
  $variables['view_links'] = array();
  _get_solr_results($islandora_object, $variables);
}

function upitt_islandora_solr_search_extras_preprocess_islandora_basic_collection_list(&$variables) {
// dpm('basic collection list');
  $islandora_object = $variables['islandora_object'];
  $variables['view_links'] = array();
  _get_solr_results($islandora_object, $variables);
}

function upitt_islandora_solr_search_extras_preprocess_islandora_basic_collection_grid(&$variables) {
// dpm('basic collection grid');
 dpm($variables);
  $islandora_object = $variables['islandora_object'];
  $variables['view_links'] = array();
  _get_solr_results($islandora_object, $variables);
}

function upitt_islandora_solr_search_extras_preprocess_islandora_objects_list(&$variables) {
// dpm('objects list');
  $islandora_object = menu_get_object('islandora_object', 2);
  _get_solr_results($islandora_object, $variables);
}

function upitt_islandora_solr_search_extras_preprocess_islandora_objects_grid(&$variables) {
  $variables['page']['sidebar'] = _get_solr_sidebar_blocks();
   dpm($variables); 

  $islandora_object = menu_get_object('islandora_object', 2);
  $variables['view_links'] = array();
  $variables['total_count'] = _get_solr_results($islandora_object, $variables);
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
  $variables['solr_search'] = islandora_solr($solr_query);
   dpm($variables['solr_search']);
  return 99999;
}

function _get_solr_sidebar_blocks() {
  $sort_block = module_invoke('islandora_solr', 'block_view', 'sort');
  $facets_block = module_invoke('islandora_solr', 'block_view', 'basic_facets');
  return _my_theme_solr_block($sort_block, 'upitt_islandora_solr_search_extras', 'sort') .
    _my_theme_solr_block($facets_block, 'upitt_islandora_solr_search_extras', 'basic_facets');
}

function _my_theme_solr_block($block, $block_module, $block_delta) {
  return '<div id="' . drupal_html_id('block-' . $block_module . '-' . $block_delta) . '" class="block-wrapper">
' . (isset($block['subject']) ? '
  <h2>' . $block['subject'] . '</h2>' : '') .
'  <div class="content">
    ' . $block['content'] .
'  </div>
</div> ';
}


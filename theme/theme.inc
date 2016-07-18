<?php

/**
 * @file
 * Theme hooks.
 */

function upitt_islandora_solr_search_extras_preprocess_islandora_objects_subset(&$variables) {
  error_log('in upitt_islandora_solr_search_extras_preprocess_islandora_objects_subset');
  $islandora_object = menu_get_object('islandora_object', 2);
  _get_solr_results($islandora_object, $variables);
  module_load_include('inc', 'islandora', 'includes/metadata');
  if ($islandora_object) {
    $page_number = (empty($_GET['page'])) ? 0 : $_GET['page'];
    $page_size = (empty($_GET['pagesize'])) ? variable_get('islandora_basic_collection_page_size', '10') : $_GET['pagesize'];

    if (isset($islandora_object['TN_LARGE'])) {
      $collection_tn_url = url("islandora/object/{$islandora_object->id}/datastream/TN_LARGE/view");
      $params = array(
        'title' => $islandora_object->label,
        'alt' => $islandora_object->label,
        'path' => $collection_tn_url);
      $variables['collection_img'] = theme('image', $params);
    }
    $variables['collection_metadata'] = islandora_retrieve_metadata_markup($islandora_object);
  }
  $variables['whamjack_sidebar'] = _get_solr_sidebar_blocks()."<hr><p>a quick brown fox jumped over the lazy dog</p>";
  $variables['display_links'] = array();
  $variables['pager'] = '';
}

function upitt_islandora_solr_search_extras_preprocess_islandora_objects_extras(&$variables) {
  error_log('islandora objects');
  $variables['theme_hook_suggestions'][] = 'islandora_objects_extras';
  $variables['display_links'] = array();
  $variables['view_links'] = array();
}

function upitt_islandora_solr_search_extras_preprocess_islandora_basic_collection_wrapper(&$variables) {
  error_log('collection wrapper');
  $islandora_object = $variables['islandora_object'];
  $variables['view_links'] = array();
}

function upitt_islandora_solr_search_extras_preprocess_islandora_basic_collection(&$variables) {
  error_log('basic collection');
  $islandora_object = $variables['islandora_object'];
  $variables['view_links'] = array();
  _get_solr_results($islandora_object, $variables);
}

function upitt_islandora_solr_search_extras_preprocess_islandora_basic_collection_list(&$variables) {
  error_log('basic collection list');
  $islandora_object = $variables['islandora_object'];
  $variables['view_links'] = array();
  _get_solr_results($islandora_object, $variables);
}

function upitt_islandora_solr_search_extras_preprocess_islandora_basic_collection_grid(&$variables) {
  error_log('basic collection grid');
  $islandora_object = $variables['islandora_object'];
  $variables['view_links'] = array();
  _get_solr_results($islandora_object, $variables);
}

function upitt_islandora_solr_search_extras_preprocess_islandora_objects_list(&$variables) {
  error_log('objects list');
  $islandora_object = menu_get_object('islandora_object', 2);
  _get_solr_results($islandora_object, $variables);
}

function upitt_islandora_solr_search_extras_preprocess_islandora_objects_grid(&$variables) {
  error_log('in upitt_islandora_solr_search_extras_preprocess_islandora_objects_grid');
  $variables['whamjack_sidebar'] = ''; 
//  $variables['whamjack_sidebar'] = _get_solr_sidebar_blocks();

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
  if (isset($variables['solr_search']) && $variables['solr_search'] <> '') { return; }
  error_log('in _get_solr_results');
  // Inspect the islandora_object to get the PID match for the SOLR query.
  $solr_query = 'RELS_EXT_isMemberOfCollection_uri_ms:"info:fedora/' . $islandora_object->id . '"';
  $variables['solr_search'] = islandora_solr($solr_query);
}

function _get_solr_sidebar_blocks() {
  error_log('in _get_solr_sidebar_blocks');
  $sort_block = module_invoke('islandora_solr', 'block_view', 'sort');
  $facets_block = module_invoke('islandora_solr', 'block_view', 'basic_facets');
  return '
        <div class="region region-sidebar">' .
_my_theme_solr_block($sort_block, 'upitt_islandora_solr_search_extras', 'sort') .
    _my_theme_solr_block($facets_block, 'upitt_islandora_solr_search_extras', 'basic_facets') . '
        </div>
';
}

function _my_theme_solr_block($block, $block_module, $block_delta) {
  return '
<div id="' . drupal_html_id('block-islandora-solr-' . $block_delta) . '" class="block-wrapper">
' . (isset($block['subject']) ? '
  <h2>' . $block['subject'] . '</h2>' : '') .
'  <div class="content">
    ' . $block['content'] .
'  </div>
</div> 
';
}

